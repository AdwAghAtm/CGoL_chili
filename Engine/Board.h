#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"

#define SECRET_NUMBER 20010901
#define MENU_WIDTH_PLACEHOLDER 150

class Board
{
public:

	int GetCursorPositionOnBoard( int cursorX, int cursorY) ;

	// Board info

	static int FrameLength; //made it variable so we can change size in future
		//Graphics::SquareSize;
	static const int BetweenFrameMarginLength = 1; //net's width
	static const int BoardStartX = Graphics::FrameWidth;
	static const int BoardStartY = Graphics::FrameWidth;
	static const int FrameCountX = 1000; 
		//(Graphics::ScreenWidth - MENU_WIDTH_PLACEHOLDER - 2 * Graphics::FrameWidth) / (FrameLength + BetweenFrameMarginLength) + 1;
		//(Graphics::ScreenWidth * Graphics::FrameWidth + 2) / (FrameLength + BetweenFrameMarginLength) + 1;
	static const int FrameCountY = 1000;
		//(Graphics::ScreenHeight - 2 * Graphics::FrameWidth) / (FrameLength + BetweenFrameMarginLength) + 1;
		//(Graphics::ScreenHeight * Graphics::FrameWidth + 2) / (FrameLength + BetweenFrameMarginLength) + 1;

	bool IsCursorOnBoard(int cursorX, int cursorY);

	int MoveCalc( int*** lvl, int startX, int startY, int dir, int prog=0 ); //dir: 1-N, 2-S, 3-E, 4-W
	int DirectionMove( int startX, int startY, int endX, int endY );

	void helpDir( int dir, int x1,int& x2,int y1,int& y2, int dt );

//private:

	static const int BoardEndX = Graphics::ScreenWidth - Graphics::FrameWidth - MENU_WIDTH_PLACEHOLDER;
		//BoardStartX + (FrameCountX) * FrameLength + BetweenFrameMarginLength * (FrameCountX + 1);
	static const int BoardEndY = Graphics::ScreenHeight - Graphics::FrameWidth;
	//BoardStartY + (FrameCountY) * FrameLength + BetweenFrameMarginLength * (FrameCountY + 1);
};