#include "Board.h"
#include "Board.h"
#include <iostream>

unsigned int Board::FrameLength = 50;
unsigned int Board::BetweenFrameMarginLength = Board::FrameLength/10;

int Board::OffsetX = -Board::FrameCountX * (Board::FrameLength + Board::BetweenFrameMarginLength) / 2;
int Board::OffsetY = -Board::FrameCountY * (Board::FrameLength + Board::BetweenFrameMarginLength) / 2;

int Board::BoardStartX = Graphics::BoardFrameWidth + Graphics::MenuThicknessLeft + Graphics::WindowFrameWidth + Board::OffsetX;
int Board::BoardStartY = Graphics::BoardFrameWidth + Graphics::MenuThicknessTop + Graphics::WindowFrameWidth + Board::OffsetY;

int Board::BoardEndX = BoardStartX + (FrameCountX)*FrameLength + BetweenFrameMarginLength * (FrameCountX + 1);
//Graphics::ScreenWidth - Graphics::BoardFrameWidth - Graphics::MenuThicknessRight - Graphics::WindowFrameWidth;
int Board::BoardEndY = BoardStartY + (FrameCountY)*FrameLength + BetweenFrameMarginLength * (FrameCountY + 1);
//Graphics::ScreenHeight - Graphics::BoardFrameWidth - Graphics::MenuThicknessBottom - Graphics::WindowFrameWidth;

int Board::GetCursorPositionOnBoard( int cursorX, int cursorY )
//it's already assumed that the cursor is on the board
{
	if( !IsCursorOnBoard( cursorX, cursorY ) ) return -1;

	int cursorAreaX = ((cursorX + FrameLength - BoardStartX) / (FrameLength + BetweenFrameMarginLength));
	int cursorAreaY = ((cursorY + FrameLength - BoardStartY) / (FrameLength + BetweenFrameMarginLength));

	return cursorAreaX + cursorAreaY * ( FrameCountX + 2 );

}

bool Board::IsCursorOnBoard(int cursorX, int cursorY) 
{
	return (
		cursorX > BoardStartX &&
		cursorX < BoardEndX &&
		cursorY > BoardStartY &&
		cursorY < BoardEndY
		);
}
