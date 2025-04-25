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
int tempClickClick = 0;

int mousePos; // id of square at mouse's position
int*** board; // 3D array of board

Mouse::Event mouseEvent; // neccessary for scrolling

void free_data(int ***data, size_t xlen, size_t ylen)
{
	size_t i, j;

	for (i=0; i < xlen; ++i) {
		if (data[i] != NULL) {
			for (j=0; j < ylen; ++j)
				free(data[i][j]);
			free(data[i]);
		}
	}
	free(data);
}

int ***alloc_data(size_t xlen, size_t ylen)
{
	int ***p;
	size_t i, j;

	if( (p = (int***)malloc( xlen * sizeof *p ) ) == NULL) 
	{
		perror("malloc 1");
		return NULL;
	}

	for (i=0; i < xlen; ++i)
		p[i] = NULL;

	for (i=0; i < xlen; ++i)
		if ((p[i] = (int**)malloc(ylen * sizeof *p[i])) == NULL) {
			perror("malloc 2");
			free_data(p, xlen, ylen);
			return NULL;
		}

	for (i=0; i < xlen; ++i)
		for (j=0; j < ylen; ++j)
			p[i][j] = NULL;

	for (i=0; i < xlen; ++i)
		for (j=0; j < ylen; ++j)
			if ((p[i][j] = (int*)malloc( 5 * sizeof *p[i][j])) == NULL) {
				perror("malloc 3");
				free_data(p, xlen, ylen);
				return NULL;
			}

	return p;
}


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
	board = alloc_data(Board::FrameCountX + 2, Board::FrameCountY + 2);
	//setting initial board to 0's	 
	for (int i = 0; i < Board::FrameCountX + 2; i++)	for (int j = 0; j < Board::FrameCountY + 2; j++)	board[i][j][0] = 0;
}
Game::~Game()
{
	//freeing memory
	free_data(board, Board::FrameCountX + 2, Board::FrameCountY + 2);
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

	mouseEvent = wnd.mouse.Read();

	if (wnd.kbd.KeyIsPressed(VK_UP) || mouseEvent.GetType() == Mouse::Event::Type::WheelUp ) 
	{		//resize board with up and down arrows or mouse scrolling
		if (Board::FrameLength < Board::MaxFrameLength)
			Board::FrameLength += 2;
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN) || mouseEvent.GetType() == Mouse::Event::Type::WheelDown )
	{
		if (Board::FrameLength > Board::MinFrameLength)
			Board::FrameLength -= 2;
	}

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
		//board[mousePos][0][0] = 1;
		/*drw.DrawCircle( xStart, yStart, 14, Colors::Gray );
		drw.DrawLine( xStart, yStart, xEnd, yEnd, Colors::Yellow );
		drw.DrawCircle( xEnd, yEnd, 14, Colors::Gray );*/
	}

if ( brd.IsCursorOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY()))
{
	mousePos = brd.GetCursorPositionOnBoard(wnd.mouse.GetPosX(), wnd.mouse.GetPosY());

	int x = mousePos % (Board::FrameCountX + 2);
	int y = mousePos / (Board::FrameCountX + 2);

	if (wnd.mouse.LeftIsPressed() )
		board[x][y][0] = 1; // draw

	if (wnd.mouse.RightIsPressed())
		board[x][y][0] = 0; // erase
}

	if( wnd.mouse.IsInWindow() )
		tempClick = wnd.mouse.LeftIsPressed();

	if (wnd.kbd.KeyIsPressed(VK_SPACE))
		NextGeneration();

}

void Game::NextGeneration()
{
	auto newBoard = alloc_data(Board::FrameCountX + 2, Board::FrameCountY + 2);

	for (int x = 1; x < Board::FrameCountX + 1; x++)
	{
		for (int y = 1; y < Board::FrameCountY + 1; y++)
		{
			int liveNeighbors = 0;

			for (int dx = -1; dx <= 1; dx++)
				for (int dy = -1; dy <= 1; dy++)
				{
					if (dx == 0 && dy == 0) continue;
					if (board[x + dx][y + dy][0] == 1)
						liveNeighbors++;
				}

			if (board[x][y][0] == 1)
			{
				newBoard[x][y][0] = (liveNeighbors == 2 || liveNeighbors == 3) ? 1 : 0;
			}
			else
			{
				newBoard[x][y][0] = (liveNeighbors == 3) ? 1 : 0;
			}
		}
	}

	free_data(board, Board::FrameCountX + 2, Board::FrameCountY + 2);
	board = newBoard;
}


void Game::ComposeFrame()
{	
	//draw board, net and squares
	drw.DrawNet( Colors::DarkGray2 );
	for (int i = 0; i < Board::FrameCountX + 2; i++)
	{
		for (int j = 0; j < Board::FrameCountY + 2; j++)
		{
			if (board[i][j][0] == 1)drw.DrawSquare(i, j, Colors::CoalChan);
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
}
