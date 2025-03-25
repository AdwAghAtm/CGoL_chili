#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"

#define SECRET_NUMBER 20010901

class Board
{
public:

	int GetCursorPositionOnBoard( int cursorX, int cursorY) ;

	// Board info

	static const int FrameLength = Graphics::FrameWidth;
	static const int BetweenFrameMarginLength = 1; //net's width
	static const int BoardStartX = Graphics::FrameWidth;
	static const int BoardStartY = Graphics::FrameWidth;
	static const int FrameCountX = (Graphics::ScreenWidth-2*Graphics::FrameWidth) / (FrameLength + BetweenFrameMarginLength)+1;
	static const int FrameCountY = (Graphics::ScreenHeight-2*Graphics::FrameWidth) / (FrameLength + BetweenFrameMarginLength)+1;
	bool IsCursorOnBoard(int cursorX, int cursorY);

	int MoveCalc( int*** lvl, int startX, int startY, int dir, int prog=0 ); //dir: 1-N, 2-S, 3-E, 4-W
	int DirectionMove( int startX, int startY, int endX, int endY );

	void helpDir( int dir, int x1,int& x2,int y1,int& y2, int dt );

private:

	static const int BoardEndX = BoardStartX + (FrameCountX) * FrameLength + BetweenFrameMarginLength * (FrameCountX + 1);
	static const int BoardEndY = BoardStartY + (FrameCountY) * FrameLength + BetweenFrameMarginLength * (FrameCountY + 1);

};