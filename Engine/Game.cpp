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
#include "MainWindow.h"
#include "Game.h"

int xStart, xEnd,
	yStart, yEnd; // start/end coordinates of mouse cursor's click

bool tempClick; // bool if mouse is clicked
int tempClickClick = 0;
bool runGame = false;
bool tempRunGame = false;
bool isPanning = false;
int lastMouseX = 0;
int lastMouseY = 0;

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
	// Board initialization is now handled by Logic class
}

Game::~Game()
{
	// Memory cleanup is now handled by Logic class
}

void Game::Go()
{
	dspl.ComposeFrame(logic.GetBoard());
	UpdateModel();
}
void Game::UpdateModel()
{

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

	// Handle zooming with mouse wheel or arrow keys
	if ((wnd.kbd.KeyIsPressed(VK_OEM_PLUS) || mouseEvent.GetType() == Mouse::Event::Type::WheelUp) && 
		!wnd.kbd.KeyIsPressed(VK_SHIFT)) 
	{
		if (Board::FrameLength < Board::MaxFrameLength)
		{
			Board::FrameLength += 2;
			// Recenter or adjust board position after zoom
			brd.UpdateBoardBoundaries();
		}
	}
	else if ((wnd.kbd.KeyIsPressed(VK_OEM_MINUS) || mouseEvent.GetType() == Mouse::Event::Type::WheelDown) && 
			 !wnd.kbd.KeyIsPressed(VK_SHIFT))
	{
		if (Board::FrameLength > Board::MinFrameLength)
		{
			Board::FrameLength -= 2;
			// Recenter or adjust board position after zoom
			brd.UpdateBoardBoundaries();
		}
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
		
		// Decide if we're panning or toggling cells based on modifier keys
		isPanning = wnd.kbd.KeyIsPressed(VK_SHIFT);
	}
	
	if (wnd.mouse.LeftIsPressed() && isPanning)
	{
		// Handle drag panning
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
		// Handle cell toggling
		mousePos = brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
		
		if (mousePos > -1)
		{
			int x = mousePos % (Board::FrameCountX + 2);
			int y = mousePos / (Board::FrameCountX + 2);
			
			logic.SetCell(x, y, true); // Draw
		}
	}
	
	// Handle right-click for erasing cells
	if (wnd.mouse.RightIsPressed() && brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		mousePos = brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
		
		if (mousePos > -1)
		{
			int x = mousePos % (Board::FrameCountX + 2);
			int y = mousePos / (Board::FrameCountX + 2);
			
			logic.SetCell(x, y, false); // Erase
		}
	}
	
	// Reset flags when mouse is released
	if (!wnd.mouse.LeftIsPressed())
	{
		isPanning = false;
	}
	
	tempClick = wnd.mouse.LeftIsPressed();

	if (runGame)
		NextGeneration();
}

void Game::NextGeneration()
{
	logic.NextGeneration();
}