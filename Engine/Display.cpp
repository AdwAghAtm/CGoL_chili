/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Display.cpp																			  *
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
#include "Display.h"
#include "GraphicMode.h"
#include <array>


Display::Display(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	drw(gfx)

{
	wnd.SetGraphics(&gfx);
}

Display::~Display()
{
	//freeing memory
	//free_data(board, Board::FrameCountX + 2, Board::FrameCountY + 2);
}


void Display::ComposeFrame(const Cell* const* board)
{
	//TODO make easy switch between dark/light mode

	gfx.BeginFrame();
	//drw.DrawBackground(Colors::LightBackGround);
	//drw.DrawBackground(Colors::DarkBackGround);
	GraphicMode::DrawBackground(&drw);
	
	//Draw board with net and squares
	//can decide here what graphics to use: legacy/alt (netAlt + surroundings)
	//drw.DrawNet(Colors::DarkGray2);
	//drw.DrawNetAlt(Colors::LightGray);
	//drw.DrawNetAlt(Colors::DarkGray2);

	for (int i = 0; i < Board::FrameCountX; i++)
	{
		for (int j = 0; j < Board::FrameCountY; j++)
		{
			if (board[i][j].isAlive)
			{
				GraphicMode::DrawForeground(Logic::GetNeighbors(board, i, j), i, j, &drw);
				//drw.DrawSquare(i, j, Colors::TransChan);
				//drw.DrawSurroundings(Logic::GetNeighbors(board, i, j), i, j, Colors::TransChan);
				//drw.DrawAllRoundedCorners(Logic::GetNeighbors(board, i, j), i, j, Colors::TransChan, Colors::DarkBackGround);//dont mix with legacy net
				//drw.DrawAllRoundedCorners(Logic::GetNeighbors(board, i, j), i, j, Colors::TransChan, Colors::LightBackGround)
			}
		}
	}
	
	//Draw board frame
	drw.DrawBoardFrame(Colors::DarkGray);
	
	//Draw menus/sidebars (these should always be on top)
	// Draw in specific order: left, top, right, bottom to handle corners correctly
	drw.DrawMenu(MenuPosition::Left, Colors::CocoaBean);
	drw.DrawMenu(MenuPosition::Top, Colors::DarkGreen);
	drw.DrawMenu(MenuPosition::Right, Colors::DarkGreen);
	drw.DrawMenu(MenuPosition::Bottom, Colors::DarkLightGray);
	//this should always be on top
	drw.DrawWindowFrame(Colors::Gray);
	
	gfx.EndFrame();
}
