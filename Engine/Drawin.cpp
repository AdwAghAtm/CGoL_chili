#include "Drawin.h"


Drawin::Drawin( Graphics& key )
	:
	gfx2( key )
{
}



void Drawin::DrawLine( int x0, int y0, int x1, int y1, Color c ) // Bresenham's algorithm
{
	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;

	dx = x1 - x0;
	dy = y1 - y0;

	dx1 = abs(dx);
	dy1 = abs(dy);

	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;

	if (dy1 <= dx1) {
		if (dx >= 0) {
			x = x0;
			y = y0;
			xe = x1;
		} else {
			x = x1;
			y = y1;
			xe = x0;
		}
		gfx2.PutPixel(x, y, c);
		for (i = 0; x<xe; i++) {
			x = x + 1;
			if (px<0) {
				px = px + 2 * dy1;
			} else {
				if ((dx<0 && dy<0) || (dx>0 && dy>0)) {
					y = y + 1;
				} else {
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			gfx2.PutPixel(x, y, c);
		}
	} else {
		if (dy >= 0) {
			x = x0;
			y = y0;
			ye = y1;
		} else {
			x = x1;
			y = y1;
			ye = y0;
		}
		gfx2.PutPixel(x, y, c);
		for (i = 0; y<ye; i++) {
			y = y + 1;
			if (py <= 0) {
				py = py + 2 * dx1;
			} else {
				if ((dx<0 && dy<0) || (dx>0 && dy>0)) {
					x = x + 1;
				} else {
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			gfx2.PutPixel(x, y, c);
		}
	}
}

void Drawin::DrawCircle(int x0, int y0, int r, Color c) // Bresenham's algorithm
{
	int x = r;
	int y = 0;
	int decision = 4 - 2 * r;

	while (y <= x) {
		gfx2.PutPixel(x + x0, y + y0, c);
		gfx2.PutPixel(y + x0, x + y0, c);
		gfx2.PutPixel(-x + x0, y + y0, c);
		gfx2.PutPixel(-y + x0, x + y0, c);
		gfx2.PutPixel(-x + x0, -y + y0, c);
		gfx2.PutPixel(-y + x0, -x + y0, c);
		gfx2.PutPixel(x + x0, -y + y0, c);
		gfx2.PutPixel(y + x0, -x + y0, c);
		if (decision < 0) {
			decision += 4 * y + 6;
		} else {
			decision += 4 * (y - x) + 10;
			x--;
		}
		y++;
	}
}

void Drawin::DrawSquare( int cord, Color c )
{	
	int tempx,tempy;
	//top left coordinates
	tempx = ( cord % (Board::FrameCountX+2) )*( Board::FrameLength + Board::BetweenFrameMarginLength ) 
		- Board::FrameLength - Board::BetweenFrameMarginLength + Board::BoardStartX;
	tempy = ( cord / (Board::FrameCountX+2) )*( Board::FrameLength + Board::BetweenFrameMarginLength ) 
		- Board::FrameLength - Board::BetweenFrameMarginLength + Board::BoardStartY;

	for( int i = 0; i < Board::FrameLength; i++ )
		for( int j = 0; j < Board::FrameLength; j++ )
		{
			if( tempx + i > 0 && tempx + i < Graphics::ScreenWidth && tempy + j > 0 && tempy + j < Graphics::ScreenHeight )
			{
				gfx2.PutPixel( tempx + i, tempy + j, c );
			}
		}
}


void Drawin::DrawSquare( int cord_x, int cord_y, Color c )
{	
	int tempx,tempy;
	//top left coordinates
	tempx = cord_x * ( Board::FrameLength + Board::BetweenFrameMarginLength )
		- Board::FrameLength - Board::BetweenFrameMarginLength + Board::BoardStartX;
	tempy = cord_y *  (Board::FrameLength + Board::BetweenFrameMarginLength)
		- Board::FrameLength - Board::BetweenFrameMarginLength + Board::BoardStartY;

	for( int i = 0; i < Board::FrameLength; i++ )
		for( int j = 0; j < Board::FrameLength; j++ )
		{
			if( tempx + i > 0 && tempx + i < Graphics::ScreenWidth && tempy + j > 0 && tempy + j < Graphics::ScreenHeight )
			{
				gfx2.PutPixel( tempx + i, tempy + j, c );
			}
		}
}

void Drawin::DrawRectangle(int x0, int y0, int x1, int y1, Color c) {
	for (int i = x0; i <= x1; i++) {
		for (int j = y0; j <= y1; j++) {
			gfx2.PutPixel(i, j, c);
		}
	}
}
void Drawin::DrawSlider(MenuPosition position, int startX, int startY, int endX, int endY, int value, int minValue, int maxValue, Color c)
{
	//calculate slider relative position 
	if (maxValue <= minValue)	return;
	float proportion = float(value - minValue) / float(maxValue - minValue); //error handling to avoid division by zero
	int sliderCorner, sliderSize;

	switch (position)
	{
	case MenuPosition::Top:
		sliderSize = endY - startY;

		//Calculate slider absolute position horizontally
		sliderCorner = startX + int(proportion * (endX - startX - sliderSize));
		DrawRectangle(sliderCorner, startY, sliderCorner + sliderSize, startY + sliderSize, c);
		break;

	case MenuPosition::Left:
		sliderSize = endX - startX;

		// calculate slider absolute position vertically
		sliderCorner = endY - sliderSize - int(proportion * (endY - startY - sliderSize));
		DrawRectangle(startX, sliderCorner, startX + sliderSize, sliderCorner + sliderSize, c);
		break;
	}
}


void Drawin::DrawNet( Color c )
{
	//for( int j = Board::BoardStartY; j < Board::BoardEndY; j++ )//is it for borad borders? //used to be  j < Graphics::ScreenHeight
	//{	
	//	for( int i = Board::BoardStartX; i < Board::BoardEndX; i++ ) //used to be i < Graphics::ScreenWidth
	//	{
	//		for( int frame = 0; frame < Board::BetweenFrameMarginLength; frame ++)
	//			if( (i - Board::BoardStartX)% (Board::FrameLength + Board::BetweenFrameMarginLength) == frame ) 
	//				gfx2.PutPixel( i, j, c );

	//		for( int frame = 0; frame < Board::BetweenFrameMarginLength; frame ++)
	//			if( (j - Board::BoardStartY)% (Board::FrameLength + Board::BetweenFrameMarginLength) == frame ) 
	//				gfx2.PutPixel( i, j, c );
	//	}
	//}
	for (int  i = Board::BoardStartX-1;  i < Board::BoardEndX;  i += Board::FrameLength + 1)
	{
		Drawin::DrawLine(i, Board::BoardStartY, i, Board::BoardEndY, c);
	}
	for (int i = Board::BoardStartY-1; i < Board::BoardEndY; i += Board::FrameLength + 1)
	{
		Drawin::DrawLine( Board::BoardStartX, i , Board::BoardEndX, i , c);
	}
}

void Drawin::DrawMenu(MenuPosition position, Color backgroundColor)
{
	int startX, startY, endX, endY;
	switch (position)
	{
	case MenuPosition::Top:
		startX = Graphics::WindowFrameWidth;
		startY = Graphics::WindowFrameWidth;
		endX = Graphics::ScreenWidth - Graphics::WindowFrameWidth - Graphics::MenuThicknessRight;
		endY = Graphics::WindowFrameWidth + Graphics::MenuThicknessTop;
		break;
	case MenuPosition::Bottom:
		startX = Graphics::WindowFrameWidth + Graphics::MenuThicknessLeft;
		startY = Graphics::ScreenHeight - Graphics::WindowFrameWidth - Graphics::MenuThicknessBottom;
		endX = Graphics::ScreenWidth - Graphics::WindowFrameWidth;
		endY = Graphics::ScreenHeight - Graphics::WindowFrameWidth;
		break;
	case MenuPosition::Left:
		startX = Graphics::WindowFrameWidth;
		startY = Graphics::WindowFrameWidth + Graphics::MenuThicknessTop;
		endX = Graphics::WindowFrameWidth + Graphics::MenuThicknessLeft;
		endY = Graphics::ScreenHeight - Graphics::WindowFrameWidth;
		break;
	case MenuPosition::Right:
		startX = Graphics::ScreenWidth - Graphics::WindowFrameWidth - Graphics::MenuThicknessRight;
		startY = Graphics::WindowFrameWidth;
		endX = Graphics::ScreenWidth - Graphics::WindowFrameWidth;
		endY = Graphics::ScreenHeight - Graphics::WindowFrameWidth - Graphics::MenuThicknessBottom;
		break;
	}
	DrawRectangle(startX, startY, endX, endY, backgroundColor);
	switch (position)
	{
	case MenuPosition::Top:
		//draw slider here
		
		break;
	case MenuPosition::Bottom:
		break;
	case MenuPosition::Left:
		//draw slider here
		DrawSlider(MenuPosition::Left, startX, startY, endX, endY, Board::FrameLength, Board::MinFrameLength, Board::MaxFrameLength, Colors::Red);
		break;
	case MenuPosition::Right:
		break;
	}
}

void Drawin::DrawBoardFrame(Color c)
{
	//Draws the frame around the board: top bottom left right rectangles respectively
	for (int y = Board::BoardStartY - Graphics::BoardFrameWidth; y < Board::BoardStartY; y++)
	{
		for (int x = Board::BoardStartX - Graphics::BoardFrameWidth; x < Board::BoardEndX + Graphics::BoardFrameWidth; x++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
	for (int y = Board::BoardEndY; y < Board::BoardEndY + Graphics::BoardFrameWidth; y++)
	{
		for (int x = Board::BoardStartX - Graphics::BoardFrameWidth; x < Board::BoardEndX + Graphics::BoardFrameWidth; x++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
	for (int x = Board::BoardStartX - Graphics::BoardFrameWidth; x < Board::BoardStartX; x++)
	{
		for (int y = Board::BoardStartY - Graphics::BoardFrameWidth; y < Board::BoardEndY + Graphics::BoardFrameWidth; y++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
	for (int x = Board::BoardEndX; x < Board::BoardEndX + Graphics::BoardFrameWidth; x++)
	{
		for (int y = Board::BoardStartY - Graphics::BoardFrameWidth; y < Board::BoardEndY + Graphics::BoardFrameWidth; y++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
}

void Drawin::DrawWindowFrame(Color c)
{
	//Draws the frame around the window: top bottom left right rectangles respectively
	for (int y = 0; y < Graphics::WindowFrameWidth; y++)
	{
		for (int x = 0; x < Graphics::ScreenWidth; x++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
	for (int y = Graphics::ScreenHeight - Graphics::WindowFrameWidth; y < Graphics::ScreenHeight; y++)
	{
		for (int x = 0; x < Graphics::ScreenWidth; x++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
	for (int x = 0; x < Graphics::WindowFrameWidth; x++)
	{
		for (int y = 0; y < Graphics::ScreenHeight; y++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
	for (int x = Graphics::ScreenWidth - Graphics::WindowFrameWidth; x < Graphics::ScreenWidth; x++)
	{
		for (int y = 0; y < Graphics::ScreenHeight; y++)
		{
			gfx2.PutPixel(x, y, c);
		}
	}
}