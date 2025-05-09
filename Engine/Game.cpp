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

int mousePos; // id of square at mouse's position

Mouse::Event mouseEvent; // necessary for scrolling

Game::Game(MainWindow& wnd)
	:
	dspl(wnd),
	wnd(wnd)
{
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

	if (wnd.kbd.KeyIsPressed(VK_UP) || mouseEvent.GetType() == Mouse::Event::Type::WheelUp ) 
	{		//resize board with up and down arrows or mouse scrolling
		if (Board::FrameLength < Board::MaxFrameLength)
			Board::FrameLength += 2;
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN) || mouseEvent.GetType() == Mouse::Event::Type::WheelDown)
	{
		if (Board::FrameLength > Board::MinFrameLength)
			Board::FrameLength -= 2;
	}

	if (wnd.mouse.LeftIsPressed() && !tempClick)
	{
		xStart = wnd.mouse.GetPosX();
		yStart = wnd.mouse.GetPosY();
	}

	if (tempClick && brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		xEnd = wnd.mouse.GetPosX();
		yEnd = wnd.mouse.GetPosY();

		if (brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()) > -1)
			mousePos = brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());
	}

	if (brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
	{
		mousePos = brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());

		int x = mousePos % (Board::FrameCountX + 2);
		int y = mousePos / (Board::FrameCountX + 2);

		if (wnd.mouse.LeftIsPressed())
			logic.SetCell(x, y, 1); // draw

		if (wnd.mouse.RightIsPressed())
			logic.SetCell(x, y, 0); // erase
	}

	if (wnd.mouse.IsInWindow())
		tempClick = wnd.mouse.LeftIsPressed();

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
		NextGeneration();
}

void Game::NextGeneration()
{
	logic.NextGeneration();
}