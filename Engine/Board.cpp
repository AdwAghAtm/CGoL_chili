#include "Board.h"
#include <iostream>

// Static member initialization
unsigned int Board::FrameLength = 50;
unsigned int Board::BetweenFrameMarginLength = Board::FrameLength / 10;
int Board::OffsetX = 0;
int Board::OffsetY = 0;
int Board::BoardStartX = 0;
int Board::BoardStartY = 0;
int Board::BoardEndX = 0;
int Board::BoardEndY = 0;
int Board::ViewportWidth = 0;
int Board::ViewportHeight = 0;

Board::Board()
{
	InitializeView();
}

void Board::InitializeView()
{
	// Calculate viewport dimensions (visible area)
	ViewportWidth = Graphics::ScreenWidth - 2 * Graphics::BoardFrameWidth - Graphics::MenuThicknessLeft - Graphics::MenuThicknessRight - 2 * Graphics::WindowFrameWidth;
	ViewportHeight = Graphics::ScreenHeight - 2 * Graphics::BoardFrameWidth - Graphics::MenuThicknessTop - Graphics::MenuThicknessBottom - 2 * Graphics::WindowFrameWidth;
	
	CenterView();
}

void Board::CenterView()
{
	// Calculate board size in pixels
	int boardPixelWidth = FrameCountX * (FrameLength + BetweenFrameMarginLength) + BetweenFrameMarginLength;
	int boardPixelHeight = FrameCountY * (FrameLength + BetweenFrameMarginLength) + BetweenFrameMarginLength;
	
	// Center the board in the viewport
	OffsetX = -(boardPixelWidth - ViewportWidth) / 2;
	OffsetY = -(boardPixelHeight - ViewportHeight) / 2;
	
	UpdateBoardBoundaries();
}

void Board::Pan(int deltaX, int deltaY)
{
	// Update offsets
	OffsetX += deltaX;
	OffsetY += deltaY;
	
	// Apply bounds checking for offsets if needed
	int boardPixelWidth = FrameCountX * (FrameLength + BetweenFrameMarginLength) + BetweenFrameMarginLength;
	int boardPixelHeight = FrameCountY * (FrameLength + BetweenFrameMarginLength) + BetweenFrameMarginLength;
	
	// Limit panning to keep at least part of the board visible
	if (OffsetX > 0) OffsetX = 0;
	if (OffsetY > 0) OffsetY = 0;
	
	int minOffsetX = ViewportWidth - boardPixelWidth;
	int minOffsetY = ViewportHeight - boardPixelHeight;
	
	if (OffsetX < minOffsetX) OffsetX = minOffsetX;
	if (OffsetY < minOffsetY) OffsetY = minOffsetY;
	
	UpdateBoardBoundaries();
}

void Board::UpdateBoardBoundaries()
{
	// Calculate the visible board area
	BoardStartX = Graphics::BoardFrameWidth + Graphics::MenuThicknessLeft + Graphics::WindowFrameWidth + OffsetX;
	BoardStartY = Graphics::BoardFrameWidth + Graphics::MenuThicknessTop + Graphics::WindowFrameWidth + OffsetY;
	
	BoardEndX = BoardStartX + FrameCountX * (FrameLength + BetweenFrameMarginLength) + BetweenFrameMarginLength;
	BoardEndY = BoardStartY + FrameCountY * (FrameLength + BetweenFrameMarginLength) + BetweenFrameMarginLength;
	
	// Ensure we don't go beyond the screen boundaries
	if (BoardEndX > Graphics::ScreenWidth - Graphics::BoardFrameWidth - Graphics::MenuThicknessRight - Graphics::WindowFrameWidth)
		BoardEndX = Graphics::ScreenWidth - Graphics::BoardFrameWidth - Graphics::MenuThicknessRight - Graphics::WindowFrameWidth;
	
	if (BoardEndY > Graphics::ScreenHeight - Graphics::BoardFrameWidth - Graphics::MenuThicknessBottom - Graphics::WindowFrameWidth)
		BoardEndY = Graphics::ScreenHeight - Graphics::BoardFrameWidth - Graphics::MenuThicknessBottom - Graphics::WindowFrameWidth;
}

int Board::GetCursorPositionOnBoard(int cursorX, int cursorY)
{
	// Check if cursor is on the board
	if(!IsCursorOnBoard(cursorX, cursorY)) return -1;

	// Calculate cell coordinates from cursor position, accounting for offset
	int cursorAreaX = ((cursorX - BoardStartX + BetweenFrameMarginLength) / (FrameLength + BetweenFrameMarginLength));
	int cursorAreaY = ((cursorY - BoardStartY + BetweenFrameMarginLength) / (FrameLength + BetweenFrameMarginLength));

	// Check boundaries
	if (cursorAreaX < 0 || cursorAreaX >= FrameCountX ||
		cursorAreaY < 0 || cursorAreaY >= FrameCountY)
		return -1;

	return cursorAreaX + cursorAreaY * (FrameCountX + 2);
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
