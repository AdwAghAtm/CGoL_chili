#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"

class Board
{
public:

	int GetCursorPositionOnBoard( int cursorX, int cursorY) ;
	
	// Board info
	static const int MinFrameLength = 4; //must be 2 at least
	static const int MaxFrameLength = 100;
	static unsigned int FrameLength; //made it variable so we can change size
	static unsigned int BetweenFrameMarginLength; //net's width
	static int BoardStartX;// = Graphics::BoardFrameWidth + Graphics::MenuThicknessLeft + Graphics::WindowFrameWidth;
	static int BoardStartY;// = Graphics::BoardFrameWidth + Graphics::MenuThicknessTop + Graphics::WindowFrameWidth;
	static int BoardEndX;
	static int BoardEndY;
	static int OffsetX;
	static int OffsetY;
	static const int FrameCountX = 15; //frame count is no longer calculated based on screen size bc board size is resizable
	static const int FrameCountY = 15; //but it used to be like below
		//(Graphics::ScreenWidth * Graphics::FrameWidth + 2) / (FrameLength + BetweenFrameMarginLength) + 1;

	bool IsCursorOnBoard(int cursorX, int cursorY);
};