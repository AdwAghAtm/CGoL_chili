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

int Board::MoveCalc( int*** lvl, int startX, int startY, int dir, int prog )
//directions: 1-N, 2-S, 3-E, 4-W
//if negative then it has to disappear x)
//not used, leaving it in case its useful
{

	switch( dir )
	{
	case 1: {
		if( lvl[startX][startY-1][2] == -2  )
			return SECRET_NUMBER;
		else
			if( lvl[startX][startY-1][2] != 0 || startY-1 < 0 )
				return prog;
			else
				return MoveCalc( lvl,startX,startY-1,dir,prog+1 );

		break;}

	case 2: {
		if( lvl[startX][startY+1][2] == -2  )
			return SECRET_NUMBER;
		else
			if( lvl[startX][startY+1][2] != 0 || startY+1 >= Board::FrameCountY+2 )
				return prog;
			else
				return MoveCalc( lvl,startX,startY+1,dir,prog+1 );

		break;}

	case 3: {
		if( lvl[startX+1][startY][2] == -2  )
			return SECRET_NUMBER;
		else
			if( lvl[startX+1][startY][2] != 0 || startX+1 >= Board::FrameCountX+2 )
				return prog;
			else
				return MoveCalc( lvl,startX+1,startY,dir,prog+1 );

		break;}

	case 4: {
		if( lvl[startX-1][startY][2] == -2  )
			return SECRET_NUMBER;
		else
			if( lvl[startX-1][startY][2] != 0 || startX-1 < 0 )
				return prog;
			else
				return MoveCalc( lvl,startX-1,startY,dir,prog+1 );

		break;}

	default: return 0;
	}

}

int Board::DirectionMove( int startX, int startY, int endX, int endY )
//directions: 1-N, 2-S, 3-E, 4-W
{
	if( abs(startX - endX) > abs(startY - endY))
	{ 
		if( startX < endX ) return 3;
		if( startX > endX ) return 4;
		return 0;
	}
	else if( abs(startX - endX) < abs(startY - endY) )
	{
		if( startY > endY ) return 1;
		if( startY < endY ) return 2;	
	}
	return 0;
}

void Board::helpDir( int dir, int x1,int& x2,int y1,int& y2, int dt )
{
	switch( dir )
	{
	case 1: {
		y2 = y1 - dt;
		x2 = x1;
		break;}

	case 2: {

		y2 = y1 + dt;
		x2 = x1;
		break;}

	case 3: {

		x2 = x1+dt;
		y2 = y1;
		break;}

	case 4: {

		x2 = x1-dt;
		y2 = y1;
		break;}

	default: break;
	}
}