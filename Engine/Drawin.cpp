#include "Drawin.h"


Drawin::Drawin( Graphics& key )
	:
	gfx2( key )
{
}



void Drawin::DrawLine( int x0, int y0, int x1, int y1, Color c ) //algorytm Bresenhama
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

void Drawin::DrawCircle(int x0, int y0, int r, Color c) //algorytm Bresenhama
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
	tempy = cord_y * ( Board::FrameLength + Board::BetweenFrameMarginLength )
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


void Drawin::DrawNet( Color c )
{
	for( int j = 0; j < Graphics::ScreenHeight; j++ )
	{	

		for( int i = 0; i < Graphics::ScreenWidth; i++ )
		{

			for( int frame = 0; frame < Board::BetweenFrameMarginLength; frame ++)
				if( (i - Board::BoardStartX +2 )% (Board::FrameLength + Board::BetweenFrameMarginLength) == frame ) 
					gfx2.PutPixel( i, j, c );

			for( int frame = 0; frame < Board::BetweenFrameMarginLength; frame ++)
				if( (j - Board::BoardStartY +2 )% (Board::FrameLength + Board::BetweenFrameMarginLength) == frame ) 
					gfx2.PutPixel( i, j, c );


		}
	}
}