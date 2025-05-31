#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"
#include <array>

class Board
{
public:
	Board();
	~Board();
	void InitializeView();
	void CenterView();
	static void Pan(int deltaX, int deltaY);
	static void UpdateViewport();
	static void UpdateBoardBoundaries();
	
	int GetCursorPositionOnBoard(int cursorX, int cursorY);

	// Board state management
	void InitializeBoard();
	void ClearBoard();
	void SetCell(int x, int y, bool value);
	bool GetCell(int x, int y) const;
	void ApplyRules();
	const uint8_t* GetBoardState() const { return boardState.data(); }
	int GetBoardStateSize() const { return FrameCountX * FrameCountY; }

	// Board info
	static const int MinFrameLength = 4; //must be 2 at least
	static const int MaxFrameLength = 100;
	static unsigned int FrameLength; //made it variable so we can change size
	static unsigned int NetThickness; //net's width
	
	// Board dimensions in cells
	static const int FrameCountX = 500;
	static const int FrameCountY = 309;
	
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
	std::array<uint8_t, FrameCountX * FrameCountY> boardState;
};