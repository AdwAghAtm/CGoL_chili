#include "Board.h"
#include <iostream>
#include "Logic.h"

// Initialize static members
unsigned int Board::FrameLength = 20;
unsigned int Board::NetThickness = 1;
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
	InitializeBoard();
}

Board::~Board()
{
}

void Board::InitializeBoard()
{
	boardState.fill(0);
}

void Board::ClearBoard()
{
	boardState.fill(0);
}

void Board::SetCell(int x, int y, bool value)
{
	if (x >= 0 && x < FrameCountX && y >= 0 && y < FrameCountY)
	{
		boardState[y * FrameCountX + x] = value ? 1 : 0;
	}
}

bool Board::GetCell(int x, int y) const
{
	if (x >= 0 && x < FrameCountX && y >= 0 && y < FrameCountY)
	{
		return boardState[y * FrameCountX + x] != 0;
	}
	return false;
}

void Board::ApplyRules()
{
	// Create a temporary array to store the next generation
	std::array<uint8_t, FrameCountX * FrameCountY> nextState;
	nextState.fill(0);

	// For each cell in the board
	for (int y = 0; y < FrameCountY; y++)
	{
		for (int x = 0; x < FrameCountX; x++)
		{
			// Get neighbors using Logic
			//auto neighbors = Logic::GetNeighbors(boardState.data(), x, y);
			auto neighbors = Logic::GetNeighbors2(boardState.data(), x, y);

			
			// Count live neighbors
			int neighborCount = 0;
			for (bool neighbor : neighbors)
			{
				if (neighbor) neighborCount++;
			}
			
			// Apply rules to determine next state
			bool isAlive = GetCell(x, y);
			bool newState = Logic::ApplyRules(isAlive, neighborCount);
			
			// Store in next state
			nextState[y * FrameCountX + x] = newState ? 1 : 0;
		}
	}

	// Update the board state
	boardState = nextState;
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
	int boardPixelWidth = FrameCountX * (FrameLength + NetThickness) + NetThickness;
	int boardPixelHeight = FrameCountY * (FrameLength + NetThickness) + NetThickness;
	
	// Center the board in the viewport
	OffsetX = -(boardPixelWidth - ViewportWidth) / 2;
	OffsetY = -(boardPixelHeight - ViewportHeight) / 2;
	
	UpdateBoardBoundaries();
}

void Board::UpdateViewport() {
	// Set up the viewport dimensions first
	ViewportWidth = Graphics::ScreenWidth - 2 * Graphics::BoardFrameWidth - Graphics::MenuThicknessLeft - Graphics::MenuThicknessRight - 2 * Graphics::WindowFrameWidth;
	ViewportHeight = Graphics::ScreenHeight - 2 * Graphics::BoardFrameWidth - Graphics::MenuThicknessTop - Graphics::MenuThicknessBottom - 2 * Graphics::WindowFrameWidth;
	Pan(0, 0); // Reset offsets to recalculate boundaries
	UpdateBoardBoundaries();
}

void Board::Pan(int deltaX, int deltaY)
{
	// Update offsets
	OffsetX += deltaX;
	OffsetY += deltaY;
	
	// Apply bounds checking for offsets if needed
	int boardPixelWidth = FrameCountX * (FrameLength + NetThickness) + NetThickness;
	int boardPixelHeight = FrameCountY * (FrameLength + NetThickness) + NetThickness;
	
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
	//not used
	// Calculate fixed viewport area that doesn't overlap with menus
	int fixedViewportStartX = Graphics::WindowFrameWidth + Graphics::MenuThicknessLeft + Graphics::BoardFrameWidth;
	int fixedViewportStartY = Graphics::WindowFrameWidth + Graphics::MenuThicknessTop + Graphics::BoardFrameWidth;
	//int fixedViewportEndX = Graphics::ScreenWidth - Graphics::WindowFrameWidth - Graphics::MenuThicknessRight - Graphics::BoardFrameWidth;
	//int fixedViewportEndY = Graphics::ScreenHeight - Graphics::WindowFrameWidth - Graphics::MenuThicknessBottom - Graphics::BoardFrameWidth;
	
	// Calculate the visible board area within the viewport
	BoardStartX = fixedViewportStartX + OffsetX;
	BoardStartY = fixedViewportStartY + OffsetY;
	
	// Calculate board end coordinates
	BoardEndX = BoardStartX + FrameCountX * (FrameLength + NetThickness) + NetThickness;
	BoardEndY = BoardStartY + FrameCountY * (FrameLength + NetThickness) + NetThickness;
	
	// Update viewport size (should be fixed and not change)
	//ViewportWidth = fixedViewportEndX - fixedViewportStartX;
	//ViewportHeight = fixedViewportEndY - fixedViewportStartY;
	
	//it brokes right/bot borders
	// Ensure the board stays within the fixed viewport boundaries
	/*if (BoardEndX > fixedViewportEndX)
		BoardEndX = fixedViewportEndX;
	
	if (BoardEndY > fixedViewportEndY)
		BoardEndY = fixedViewportEndY;
		*/
	// Ensure we recalculate the between frame margin when frame length changes
	// 
	
	//resize net only here, rest instances are commented
	NetThickness = FrameLength / 5;
	if (NetThickness < 1) NetThickness = 1;
}

int Board::GetCursorPositionOnBoard(int cursorX, int cursorY)
{
	// Check if cursor is on the board
	if(!IsCursorOnBoard(cursorX, cursorY)) return -1;

	// Calculate cell coordinates from cursor position, accounting for offset
	int cursorAreaX = ((cursorX - BoardStartX + NetThickness) / (FrameLength + NetThickness));
	int cursorAreaY = ((cursorY - BoardStartY + NetThickness) / (FrameLength + NetThickness));

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
