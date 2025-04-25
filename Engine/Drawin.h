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

class Drawin
{
public:


	Drawin( class Graphics& key );

	Drawin( const Drawin& ) = delete;
	Drawin& operator=( const Drawin& ) = delete;

	void DrawLine( int x0, int y0, int x1, int y1, Color c );
	void DrawCircle( int x0, int y0, int r, Color c );

	void DrawSquare( int cord, Color c );
	void DrawSquare( int cord_x, int cord_y, Color c );

	void DrawNet( Color c );
	void DrawMenu(MenuPosition position, Color backgroundColor);
	void DrawBoardFrame(Color c);
	void DrawWindowFrame(Color c);


private:


	Graphics& gfx2;

};