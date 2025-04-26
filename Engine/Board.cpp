#include "Board.h"
#include <iostream>

int Board::FrameLength = 50;

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
