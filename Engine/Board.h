#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"

class Board
{
public:
	Board();
	void InitializeView();
	void CenterView();
	void Pan(int deltaX, int deltaY);
	void UpdateBoardBoundaries();
	
	int GetCursorPositionOnBoard(int cursorX, int cursorY);
	
	// Board info
	static const int MinFrameLength = 4; //must be 2 at least
	static const int MaxFrameLength = 100;
	static unsigned int FrameLength; //made it variable so we can change size
	static unsigned int BetweenFrameMarginLength; //net's width
	
	// Board dimensions in cells
	static const int FrameCountX = 1000;
	static const int FrameCountY = 1000;
	
	// Board position and view
	static int OffsetX; // Horizontal pan offset
	static int OffsetY; // Vertical pan offset
	static int BoardStartX; // Left edge of viewable board area
	static int BoardStartY; // Top edge of viewable board area
	static int BoardEndX; // Right edge of viewable board area
	static int BoardEndY; // Bottom edge of viewable board area
	
	// Viewport dimensions (visible area of board)
	static int ViewportWidth;
	static int ViewportHeight;
	
	bool IsCursorOnBoard(int cursorX, int cursorY);

private:
};