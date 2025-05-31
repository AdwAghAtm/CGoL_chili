/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include <chrono>
#include "MainWindow.h"
#include "Game.h"
#include "GraphicMode.h"

int xStart, xEnd,
	yStart, yEnd; // start/end coordinates of mouse cursor's click

bool tempClick; // bool if mouse is clicked
int tempClickClick = 0;
bool runGame = false;
bool tempRunGame = false;
bool tempDarkmode = false;
bool tempVisuals = false;
bool isPanning = false;
int lastMouseX = 0;
int lastMouseY = 0;
unsigned int Game::targetFPS = 10;

int mousePos; // id of square at mouse's position

Mouse::Event mouseEvent; // necessary for scrolling

Game::Game(MainWindow& wnd)
	:
	dspl(wnd),
	wnd(wnd)
{
	// Initialize the board view (centers the board)
	brd.InitializeView();

}

void Game::Pre()
{
	// Initialize the board
	brd.InitializeBoard();
	brd.InitializeView();
}

Game::~Game()
{
	// Memory cleanup is now handled by Logic class
}

void Game::Go()
{
	// Get board state from Board and pass it to Display
	dspl.ComposeFrame(brd.GetBoardState());
	UpdateModel();
}

void Game::SetTargetFPS(unsigned int fps) {
	Game::targetFPS = fps;
}

int Game::GetTargetFPS(){
	return Game::targetFPS;
}

std::chrono::milliseconds Game::GetFrameDuration(){
	return std::chrono::milliseconds(1000 / Game::targetFPS);
}


void Game::UpdateModel()
{
	using clock = std::chrono::steady_clock;
	auto now = clock::now();
	

	mouseEvent = wnd.mouse.Read();

	//toggle game running (must hold spacebar for longer than 0.0000001ms to pause)
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!tempRunGame)
		{
			runGame = !runGame;
		}
		tempRunGame = true; //prevent runGame from changing simultaneously while spacebar pressed/hold
	}
	else
	{
		tempRunGame = false;
	}

	// Handle zooming with mouse wheel or plus/minus keys
	int oldFrameLength = Board::FrameLength;
	bool zoomChanged = false;
	
	if ((wnd.kbd.KeyIsPressed(VK_OEM_PLUS) || mouseEvent.GetType() == Mouse::Event::Type::WheelUp) && 
		!wnd.kbd.KeyIsPressed(VK_SHIFT)) 
	{
		if (Board::FrameLength < Board::MaxFrameLength)
		{
			// Get mouse position before zoom
			int mouseX = wnd.mouse.GetPosX();
			int mouseY = wnd.mouse.GetPosY();
			
			// Calculate board coordinates of mouse before zoom
			int mouseBoardX = mouseX - Board::BoardStartX;
			int mouseBoardY = mouseY - Board::BoardStartY;
			
			// Calculate board coordinates as a fraction of total size
			float relativeX = (float)mouseBoardX / (Board::FrameCountX * (oldFrameLength + Board::NetThickness));
			float relativeY = (float)mouseBoardY / (Board::FrameCountY * (oldFrameLength + Board::NetThickness));
			
			// Update zoom level
			Board::FrameLength += 2;
			zoomChanged = true;
			
			// Calculate new total board size
			int newBoardWidth = Board::FrameCountX * (Board::FrameLength + Board::NetThickness);
			int newBoardHeight = Board::FrameCountY * (Board::FrameLength + Board::NetThickness);
			
			// Calculate new offsets to keep the mouse point in the same relative position
			int newOffsetX = mouseX - (int)(relativeX * newBoardWidth);
			int newOffsetY = mouseY - (int)(relativeY * newBoardHeight);
			
			// Apply the new offset
			Board::OffsetX = newOffsetX - Graphics::BoardFrameWidth - Graphics::MenuThicknessLeft - Graphics::WindowFrameWidth;
			Board::OffsetY = newOffsetY - Graphics::BoardFrameWidth - Graphics::MenuThicknessTop - Graphics::WindowFrameWidth;
		}
	}
	else if ((wnd.kbd.KeyIsPressed(VK_OEM_MINUS) || mouseEvent.GetType() == Mouse::Event::Type::WheelDown) && 
			 !wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		if (Board::FrameLength > Board::MinFrameLength)
		{
			// Get mouse position before zoom
			int mouseX = wnd.mouse.GetPosX();
			int mouseY = wnd.mouse.GetPosY();
			
			// Calculate board coordinates of mouse before zoom
			int mouseBoardX = mouseX - Board::BoardStartX;
			int mouseBoardY = mouseY - Board::BoardStartY;
			
			// Calculate board coordinates as a fraction of total size
			float relativeX = (float)mouseBoardX / (Board::FrameCountX * (oldFrameLength + Board::NetThickness));
			float relativeY = (float)mouseBoardY / (Board::FrameCountY * (oldFrameLength + Board::NetThickness));
			
			// Update zoom level
			Board::FrameLength -= 2;
			zoomChanged = true;
			
			// Calculate new total board size
			int newBoardWidth = Board::FrameCountX * (Board::FrameLength + Board::NetThickness);
			int newBoardHeight = Board::FrameCountY * (Board::FrameLength + Board::NetThickness);
			
			// Calculate new offsets to keep the mouse point in the same relative position
			int newOffsetX = mouseX - (int)(relativeX * newBoardWidth);
			int newOffsetY = mouseY - (int)(relativeY * newBoardHeight);
			
			// Apply the new offset
			Board::OffsetX = newOffsetX - Graphics::BoardFrameWidth - Graphics::MenuThicknessLeft - Graphics::WindowFrameWidth;
			Board::OffsetY = newOffsetY - Graphics::BoardFrameWidth - Graphics::MenuThicknessTop - Graphics::WindowFrameWidth;
		}
	}
	
	// If zoom changed, update boundaries and apply limits
	if (zoomChanged)
	{
		brd.UpdateBoardBoundaries();
		
		// Apply additional bounds checks to ensure board stays visible
		int boardPixelWidth = Board::FrameCountX * (Board::FrameLength + Board::NetThickness);
		int boardPixelHeight = Board::FrameCountY * (Board::FrameLength + Board::NetThickness);
		int minOffsetX = Board::ViewportWidth - boardPixelWidth;
		int minOffsetY = Board::ViewportHeight - boardPixelHeight;
		
		if (Board::OffsetX > 0) Board::OffsetX = 0;
		if (Board::OffsetY > 0) Board::OffsetY = 0;
		if (Board::OffsetX < minOffsetX) Board::OffsetX = minOffsetX;
		if (Board::OffsetY < minOffsetY) Board::OffsetY = minOffsetY;
		
		// Final update of board boundaries after corrections
		brd.UpdateBoardBoundaries();
	}

	// Handle panning with arrow keys
	const int panSpeed = 10;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		brd.Pan(-panSpeed, 0);
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		brd.Pan(panSpeed, 0);
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		brd.Pan(0, -panSpeed);
	}
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		brd.Pan(0, panSpeed);
	}

	// Handle mouse input for panning and cell toggling
	if (wnd.mouse.LeftIsPressed() && !tempClick)
	{
		// Start of left-click
		xStart = wnd.mouse.GetPosX();
		yStart = wnd.mouse.GetPosY();
		lastMouseX = xStart;
		lastMouseY = yStart;
		
		// Decide if we're panning or toggling cells - reverse the logic
		// Now default is panning, shift+click to toggle cells
		isPanning = !wnd.kbd.KeyIsPressed(VK_SHIFT);
	}
	
	if (wnd.mouse.LeftIsPressed() && isPanning)
	{
		// Handle drag panning (now the default action)
		int currentX = wnd.mouse.GetPosX();
		int currentY = wnd.mouse.GetPosY();
		
		// Calculate the delta since last update and apply pan
		int deltaX = currentX - lastMouseX;
		int deltaY = currentY - lastMouseY;
		
		if (deltaX != 0 || deltaY != 0)
		{
			brd.Pan(deltaX, deltaY);
			
			// Update last position
			lastMouseX = currentX;
			lastMouseY = currentY;
		}
	}
	else if (wnd.mouse.LeftIsPressed() && !isPanning && brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		// Handle cell toggling (now requires shift key)
		mousePos = brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
		
		if (mousePos > -1)
		{
			int x = mousePos % (Board::FrameCountX + 2);
			int y = mousePos / (Board::FrameCountX + 2);
			
			brd.SetCell(x, y, true); // Draw
		}
	}
	
	// Handle right-click for erasing cells (also now requires shift key)
	if (wnd.mouse.RightIsPressed() && wnd.kbd.KeyIsPressed(VK_SHIFT) && 
		brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		mousePos = brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
		
		if (mousePos > -1)
		{
			int x = mousePos % (Board::FrameCountX + 2);
			int y = mousePos / (Board::FrameCountX + 2);
			
			brd.SetCell(x, y, false); // Erase
		}
	}
	
	// Add visual cue for the mouse cursor style - use the custom Windows cursor API
	if (wnd.kbd.KeyIsPressed(VK_SHIFT) && brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		// Would set cursor to "pen/crosshair" style if we had direct access to the Windows API
		// For now we can just log that we would change cursor here
	}
	else if (wnd.mouse.LeftIsPressed() && isPanning)
	{
		// Would set cursor to "grabbing/closed hand" style if we had direct access to the Windows API
	}
	else if (brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		// Would set cursor to "grab/open hand" style if we had direct access to the Windows API
	}
	
	// Reset flags when mouse is released
	if (!wnd.mouse.LeftIsPressed())
	{
		isPanning = false;
	}
	
	tempClick = wnd.mouse.LeftIsPressed();


	if ((wnd.kbd.KeyIsPressed(VK_OEM_MINUS) || mouseEvent.GetType() == Mouse::Event::Type::WheelDown) && wnd.kbd.KeyIsPressed(VK_SHIFT) &&
		brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		if (GetTargetFPS()>1)
		{
			SetTargetFPS(GetTargetFPS() - 1);
		}
	}
	if ((wnd.kbd.KeyIsPressed(VK_OEM_PLUS) || mouseEvent.GetType() == Mouse::Event::Type::WheelUp) && wnd.kbd.KeyIsPressed(VK_SHIFT) &&
		brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		if (GetTargetFPS() < 30)
		{
			SetTargetFPS(GetTargetFPS() + 1);
		}
	}

	//switch darkmode
	if ((wnd.kbd.KeyIsPressed(VK_F1)))
	{
		if (!tempDarkmode)
		{
			GraphicMode::SwitchDarkMode();
		}
		tempDarkmode = true; //prevent runGame from changing simultaneously while spacebar pressed/hold
	}
	else
	{
		tempDarkmode = false;
	}

	//switch graphic mode (roundness)
	if ((wnd.kbd.KeyIsPressed(VK_F1)))
	{
		if (!tempDarkmode)
		{
			GraphicMode::SwitchDarkMode();
		}
		tempDarkmode = true; //prevent runGame from changing simultaneously while spacebar pressed/hold
	}
	else
	{
		tempDarkmode = false;
	}

	//switch visuals
	if ((wnd.kbd.KeyIsPressed(VK_F2)))
	{
		if (!tempVisuals)
		{
			GraphicMode::SwitchVisuals();
		}
		tempVisuals = true; //prevent runGame from changing simultaneously while spacebar pressed/hold
	}
	else
	{
		tempVisuals = false;
	}

	auto frameDuration = std::chrono::milliseconds(1000 / targetFPS);
	// Run the game simulation if active
	if (now >= nextFrameTime)
	{
		//nested if to keep track on fps even if game paused
		if (runGame)
			NextGeneration();
		nextFrameTime += Game::GetFrameDuration();
	}

}

void Game::NextGeneration()
{
	brd.ApplyRules();
}