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



Display::Display(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	drw(gfx)

{
}

Display::~Display()
{
	//freeing memory
	//free_data(board, Board::FrameCountX + 2, Board::FrameCountY + 2);
}


void Display::ComposeFrame(const Cell* const* board)
{
	gfx.BeginFrame();
	//draw board, net and squares
	drw.DrawNet(Colors::DarkGray2);
	for (int i = 0; i < Board::FrameCountX; i++)
	{
		for (int j = 0; j < Board::FrameCountY; j++)
		{
			//here square are drawn even if not visible
			if (board[i][j].isAlive)
			{
				drw.DrawSquare(i, j, Colors::TransChan);
			}
		}
	}
	//draw menus and buttons etc
	drw.DrawMenu(MenuPosition::Top, Colors::DarkGreen);
	drw.DrawMenu(MenuPosition::Right, Colors::DarkGray2);
	drw.DrawMenu(MenuPosition::Bottom, Colors::DarkLightGray);
	drw.DrawMenu(MenuPosition::Left, Colors::CocoaBean);

	//draw visuals like frames
	drw.DrawBoardFrame(Colors::DarkGray);
	drw.DrawWindowFrame(Colors::Gray);

	gfx.EndFrame();
}
