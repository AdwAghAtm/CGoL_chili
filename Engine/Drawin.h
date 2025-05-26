#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "MainWindow.h"
#include "Board.h"

enum class MenuPosition
{
	Top,
	Bottom,
	Left,
	Right
};
enum class CornerPosition
{
	TopRight,
	BottomRight,
	BottomLeft,
	TopLeft
};

class Drawin
{
public:
	Drawin(class Graphics& key);
	Drawin( const Drawin& ) = delete;
	Drawin& operator=( const Drawin& ) = delete;

	void DrawBackground(Color c);
	void DrawLine( int x0, int y0, int x1, int y1, Color c );
	void DrawCircle( int x0, int y0, int r, Color c );
	void DrawSquare( int cord, Color c );
	void DrawSquare( int cord_x, int cord_y, Color c );
	void DrawSurroundings(std::array<bool, 9> neighbors, int cord_x, int cord_y, Color c);
	void DrawOuterCorners(int cord_x, int cord_y, Color c, Color bg);
	void DrawOuterCorners(std::array<bool, 9> neighbors, int cord_x, int cord_y, Color c, Color bg);
	void DrawInnerCorners(std::array<bool, 9> neighbors, int cord_x, int cord_y, Color c);
	void DrawAllRoundedCorners(std::array<bool, 9> neighbors, int cord_x, int cord_y, Color c, Color bg);
	void DrawRoundedCorner(CornerPosition position, int centerX, int centerY, int radius, Color c);
	void DrawRectangle(int x0, int y0, int x1, int y1, Color c);
	void DrawSlider(MenuPosition position, int startX, int startY, int endX, int endY, int value, int minValue, int maxValue, Color c);
	void DrawNetAlt(Color c);
	void DrawNet( Color c );
	void DrawMenu(MenuPosition position, Color backgroundColor);
	void DrawBoardFrame(Color c);
	void DrawWindowFrame(Color c);

private:
	// Helper methods for safe drawing
	bool IsWithinScreenBounds(int x, int y) const;
	void SafePutPixel(int x, int y, Color c);
	
	Graphics& gfx2;
};