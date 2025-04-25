#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"

#define SECRET_NUMBER 20010901
#define MENU_WIDTH_PLACEHOLDER 150
#define MENU_HEIGHT_PLACEHOLDER 100

class Board
{
public:

	int GetCursorPositionOnBoard( int cursorX, int cursorY) ;

	// Board info
	static const int MinFrameLength = 4;
	static const int MaxFrameLength = 100;
	static int FrameLength; //made it variable so we can change size
	static const int BetweenFrameMarginLength = 1; //net's width
	static const int BoardStartX = Graphics::BoardFrameWidth + Graphics::MenuThicknessLeft + Graphics::WindowFrameWidth;
	static const int BoardStartY = Graphics::BoardFrameWidth + Graphics::MenuThicknessTop + Graphics::WindowFrameWidth;
	static const int FrameCountX = 1000; //frame count is no longer calculated based on screen size bc board size is resizable
	static const int FrameCountY = 1000; //but it used to be like below
		//(Graphics::ScreenWidth * Graphics::FrameWidth + 2) / (FrameLength + BetweenFrameMarginLength) + 1;

	bool IsCursorOnBoard(int cursorX, int cursorY);

	int MoveCalc( int*** lvl, int startX, int startY, int dir, int prog=0 ); //dir: 1-N, 2-S, 3-E, 4-W
	int DirectionMove( int startX, int startY, int endX, int endY );

	void helpDir( int dir, int x1,int& x2,int y1,int& y2, int dt );

	//private: //why private?
	static const int BoardEndX = Graphics::ScreenWidth - Graphics::BoardFrameWidth - Graphics::MenuThicknessRight - Graphics::WindowFrameWidth;
		//BoardStartX + (FrameCountX) * FrameLength + BetweenFrameMarginLength * (FrameCountX + 1);
	static const int BoardEndY = Graphics::ScreenHeight - Graphics::BoardFrameWidth - Graphics::MenuThicknessBottom - Graphics::WindowFrameWidth;
		//BoardStartY + (FrameCountY) * FrameLength + BetweenFrameMarginLength * (FrameCountY + 1);
};