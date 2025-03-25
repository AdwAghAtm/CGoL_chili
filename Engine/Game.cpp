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

int xStart,xEnd,
		yStart,yEnd; // start/end coordinates of mouse cursor's click

bool tempClick; // bool if mouse is clicked

int mousePos; // id of square at mouse's position

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	drw( gfx )
{
}

void Game::Pre()
{
	//allocating memory
}


void Game::Go()
{
	gfx.BeginFrame();	

	ComposeFrame();
	UpdateModel();

	gfx.EndFrame();
}

void Game::UpdateModel()
{

	if( wnd.mouse.LeftIsPressed() && !tempClick )
	{
		xStart = wnd.mouse.GetPosX();
		yStart = wnd.mouse.GetPosY();
	}



	if( tempClick  && brd.IsCursorOnBoard( wnd.mouse.GetPosX(),wnd.mouse.GetPosY() )  ) 
	{
		xEnd = wnd.mouse.GetPosX();
		yEnd = wnd.mouse.GetPosY();

		if(	brd.GetCursorPositionOnBoard( wnd.mouse.GetPosX(),wnd.mouse.GetPosY() ) > -1 )
			mousePos = brd.GetCursorPositionOnBoard( wnd.mouse.GetPosX(),wnd.mouse.GetPosY());

		drw.DrawSquare(mousePos, Colors::Lime);
		/*drw.DrawCircle( xStart, yStart, 14, Colors::Gray );
		drw.DrawLine( xStart, yStart, xEnd, yEnd, Colors::Yellow );
		drw.DrawCircle( xEnd, yEnd, 14, Colors::Gray );*/

	}

	

	if( wnd.mouse.IsInWindow() )
		tempClick = wnd.mouse.LeftIsPressed();
}

void Game::ComposeFrame()
{
	drw.DrawNet( Colors::DarkGray2 );
	drw.DrawCircle( 250, 250, 20, Colors::White );
	drw.DrawCircle(250, 250, 10, Colors::Red);

}
