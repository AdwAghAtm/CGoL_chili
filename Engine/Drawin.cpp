#include "Drawin.h"


Drawin::Drawin( Graphics& key )
	:
	gfx2( key )
{
}

// Helper function to check if coordinates are within screen bounds
bool Drawin::IsWithinScreenBounds(int x, int y) const
{
	return (x >= 0 && x < Graphics::ScreenWidth && y >= 0 && y < Graphics::ScreenHeight);
}

// Safe version of PutPixel that checks boundaries
void Drawin::SafePutPixel(int x, int y, Color c)
{
	if (IsWithinScreenBounds(x, y))
	{
		gfx2.PutPixel(x, y, c);
	}
}

void Drawin::DrawLine( int x0, int y0, int x1, int y1, Color c ) // Bresenham's algorithm
{
	// Clip the line to the screen boundaries
	// This is a simple implementation - more advanced clipping algorithms exist
	if (x0 < 0 && x1 < 0) return; // Line is completely off-screen left
	if (y0 < 0 && y1 < 0) return; // Line is completely off-screen top
	if (x0 >= Graphics::ScreenWidth && x1 >= Graphics::ScreenWidth) return; // Line is completely off-screen right
	if (y0 >= Graphics::ScreenHeight && y1 >= Graphics::ScreenHeight) return; // Line is completely off-screen bottom
	
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
		
		SafePutPixel(x, y, c);
		
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
			SafePutPixel(x, y, c);
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
		
		SafePutPixel(x, y, c);
		
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
			SafePutPixel(x, y, c);
		}
	}
}

void Drawin::DrawCircle(int x0, int y0, int r, Color c) // Bresenham's algorithm
{
	// Skip if circle is entirely off screen
	if (x0 + r < 0 || x0 - r >= Graphics::ScreenWidth || 
		y0 + r < 0 || y0 - r >= Graphics::ScreenHeight)
	{
		return;
	}

	int x = r;
	int y = 0;
	int decision = 4 - 2 * r;

	while (y <= x) {
		SafePutPixel(x + x0, y + y0, c);
		SafePutPixel(y + x0, x + y0, c);
		SafePutPixel(-x + x0, y + y0, c);
		SafePutPixel(-y + x0, x + y0, c);
		SafePutPixel(-x + x0, -y + y0, c);
		SafePutPixel(-y + x0, -x + y0, c);
		SafePutPixel(x + x0, -y + y0, c);
		SafePutPixel(y + x0, -x + y0, c);
		
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

	// Clip to screen boundaries
	if (tempx + Board::FrameLength < 0 || tempx >= Graphics::ScreenWidth ||
		tempy + Board::FrameLength < 0 || tempy >= Graphics::ScreenHeight)
	{
		return; // Square is entirely off-screen
	}

	for( int i = 0; i < Board::FrameLength; i++ )
		for( int j = 0; j < Board::FrameLength; j++ )
		{
			SafePutPixel( tempx + i, tempy + j, c );
		}
}


void Drawin::DrawSquare( int cord_x, int cord_y, Color c )
{	
    // Calculate the absolute pixel position for this cell
    int tempx = Board::BoardStartX + cord_x * (Board::FrameLength + Board::BetweenFrameMarginLength);
    int tempy = Board::BoardStartY + cord_y * (Board::FrameLength + Board::BetweenFrameMarginLength);
    
    // Check if the square is in the visible area before drawing
    if (tempx + Board::FrameLength < 0 || 
        tempx >= Graphics::ScreenWidth || 
        tempy + Board::FrameLength < 0 || 
        tempy >= Graphics::ScreenHeight)
    {
        return; // Cell is outside the visible area, don't draw it
    }
    
    // Use the optimized rectangle drawing method with clipping
    DrawRectangle(tempx, tempy, tempx + Board::FrameLength - 1, tempy + Board::FrameLength - 1, c);
}

void Drawin::DrawRectangle(int x0, int y0, int x1, int y1, Color c) {
	// Clip rectangle to screen bounds
	x0 = std::max(0, x0);
	y0 = std::max(0, y0);
	x1 = std::min(Graphics::ScreenWidth - 1, x1);
	y1 = std::min(Graphics::ScreenHeight - 1, y1);
	
	// Check if rectangle is still visible after clipping
	if (x0 > x1 || y0 > y1) {
		return; // Rectangle is entirely off-screen
	}
	
	for (int i = x0; i <= x1; i++) {
		for (int j = y0; j <= y1; j++) {
			gfx2.PutPixel(i, j, c); // Direct call is safe here since we clipped the coordinates
		}
	}
}

void Drawin::DrawSlider(MenuPosition position, int startX, int startY, int endX, int endY, int value, int minValue, int maxValue, Color c)
{
    // Calculate slider relative position 
    if (maxValue <= minValue) return;
    
    // Calculate proportion based on current value
    float proportion = float(value - minValue) / float(maxValue - minValue);
    
    // Fixed slider thickness regardless of board zoom/position
    const int sliderThickness = 5;
    int sliderCorner, sliderSize;

    switch (position)
    {
    case MenuPosition::Top:
        sliderSize = std::min(endY - startY, sliderThickness);
        
        // Calculate slider absolute position horizontally
        sliderCorner = startX + int(proportion * (endX - startX - sliderSize));
        
        // Ensure slider stays within menu bounds
        sliderCorner = std::max(startX, std::min(sliderCorner, endX - sliderSize));
        
        // Draw the slider with direct rectangle drawing to ensure it appears
        DrawRectangle(sliderCorner, startY, sliderCorner + sliderSize, endY - 1, c);
        break;

    case MenuPosition::Left:
        sliderSize = std::min(endX - startX, sliderThickness);
        
        // Calculate slider absolute position vertically (reverse direction for intuitive feel)
        sliderCorner = startY + int((1.0f - proportion) * (endY - startY - sliderSize));
        
        // Ensure slider stays within menu bounds
        sliderCorner = std::max(startY, std::min(sliderCorner, endY - sliderSize));
        
        // Draw the slider with direct rectangle drawing to ensure it appears
        DrawRectangle(startX, sliderCorner, endX - 1, sliderCorner + sliderSize, c);
        break;
    }
}


void Drawin::DrawNet(Color c)
{
    // Calculate visible area bounds
    int visibleStartX = std::max(0, Board::BoardStartX);
    int visibleStartY = std::max(0, Board::BoardStartY);
    int visibleEndX = std::min(Graphics::ScreenWidth, Board::BoardEndX);
    int visibleEndY = std::min(Graphics::ScreenHeight, Board::BoardEndY);
    
    // Skip if no part of the board is visible
    if (visibleStartX >= visibleEndX || visibleStartY >= visibleEndY) {
        return;
    }
    
    // Calculate cell size and spacing
    int cellSize = Board::FrameLength;
    int gridSpacing = cellSize + Board::BetweenFrameMarginLength;
    
    // Calculate the cell grid indices that would contain the visible area
    int firstColIdx = std::max(0, (visibleStartX - Board::BoardStartX) / gridSpacing);
    int firstRowIdx = std::max(0, (visibleStartY - Board::BoardStartY) / gridSpacing);
    int lastColIdx = std::min(Board::FrameCountX, (visibleEndX - Board::BoardStartX) / gridSpacing + 1);
    int lastRowIdx = std::min(Board::FrameCountY, (visibleEndY - Board::BoardStartY) / gridSpacing + 1);
    
    // Draw vertical grid lines
    for (int col = firstColIdx; col <= lastColIdx; col++) {
        // Line X position in screen space
        int lineX = Board::BoardStartX + col * gridSpacing - Board::BetweenFrameMarginLength;
        
        // If beyond visible area, skip
        if (lineX + Board::BetweenFrameMarginLength <= visibleStartX || lineX >= visibleEndX) {
            continue;
        }
        
        // Draw the grid line (thicker line based on BetweenFrameMarginLength)
        for (int thickness = 0; thickness < Board::BetweenFrameMarginLength; thickness++) {
            int x = lineX + thickness;
            if (x >= 0 && x < Graphics::ScreenWidth) {
                DrawLine(x, visibleStartY, x, visibleEndY - 1, c);
            }
        }
    }
    
    // Draw horizontal grid lines
    for (int row = firstRowIdx; row <= lastRowIdx; row++) {
        // Line Y position in screen space
        int lineY = Board::BoardStartY + row * gridSpacing - Board::BetweenFrameMarginLength;
        
        // If beyond visible area, skip
        if (lineY + Board::BetweenFrameMarginLength <= visibleStartY || lineY >= visibleEndY) {
            continue;
        }
        
        // Draw the grid line (thicker line based on BetweenFrameMarginLength)
        for (int thickness = 0; thickness < Board::BetweenFrameMarginLength; thickness++) {
            int y = lineY + thickness;
            if (y >= 0 && y < Graphics::ScreenHeight) {
                DrawLine(visibleStartX, y, visibleEndX - 1, y, c);
            }
        }
    }
}

void Drawin::DrawMenu(MenuPosition position, Color backgroundColor)
{
    // Menu positions and sizes are fixed constants based on Graphics settings
    // They are completely independent of Board position or zoom
    int startX, startY, endX, endY;
    
    // Calculate menu bounds based on screen size and fixed margins
    // Ensure menus extend fully to screen edges
    switch (position)
    {
    case MenuPosition::Top:
        startX = 0;  // Extend to left edge
        startY = 0;  // Extend to top edge
        endX = Graphics::ScreenWidth;  // Extend to right edge
        endY = Graphics::WindowFrameWidth + Graphics::MenuThicknessTop;
        break;
    case MenuPosition::Bottom:
        startX = 0;  // Extend to left edge
        startY = Graphics::ScreenHeight - Graphics::WindowFrameWidth - Graphics::MenuThicknessBottom;
        endX = Graphics::ScreenWidth;  // Extend to right edge
        endY = Graphics::ScreenHeight;  // Extend to bottom edge
        break;
    case MenuPosition::Left:
        startX = 0;  // Extend to left edge
        startY = 0;  // Extend to top edge
        endX = Graphics::WindowFrameWidth + Graphics::MenuThicknessLeft;
        endY = Graphics::ScreenHeight;  // Extend to bottom edge
        break;
    case MenuPosition::Right:
        startX = Graphics::ScreenWidth - Graphics::WindowFrameWidth - Graphics::MenuThicknessRight;
        startY = 0;  // Extend to top edge
        endX = Graphics::ScreenWidth;  // Extend to right edge
        endY = Graphics::ScreenHeight;  // Extend to bottom edge
        break;
    }
    
    // Draw the menu background - use direct pixel drawing for maximum control
    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            gfx2.PutPixel(x, y, backgroundColor);
        }
    }
    
    // Add controls to the menus
    switch (position)
    {
    case MenuPosition::Top:
        // Top menu controls (if any)
        break;
    case MenuPosition::Bottom:
        // Bottom menu controls (if any)
        break;
    case MenuPosition::Left:
        // Left menu - draw zoom level slider
        // Use a fixed width for the slider that doesn't depend on Board variables
        DrawSlider(MenuPosition::Left, 
                  startX + 2,           // Add a small margin
                  startY + 20,          // Position down from top
                  endX - 2,             // Full width minus margin
                  endY - 20,            // Leave space at bottom
                  Board::FrameLength,   // Current value
                  Board::MinFrameLength, // Minimum value
                  Board::MaxFrameLength, // Maximum value
                  Colors::Red);         // Slider color
        break;
    case MenuPosition::Right:
        // Right menu controls (if any)
        break;
    }
    
    // Draw a border around the menu for visual clarity
    Color borderColor = Colors::Gray;
    
    // Top border
    for (int x = startX; x < endX; x++) {
        gfx2.PutPixel(x, startY, borderColor);
        gfx2.PutPixel(x, startY + 1, borderColor);
    }
    
    // Bottom border
    for (int x = startX; x < endX; x++) {
        gfx2.PutPixel(x, endY - 1, borderColor);
        gfx2.PutPixel(x, endY - 2, borderColor);
    }
    
    // Left border
    for (int y = startY; y < endY; y++) {
        gfx2.PutPixel(startX, y, borderColor);
        gfx2.PutPixel(startX + 1, y, borderColor);
    }
    
    // Right border
    for (int y = startY; y < endY; y++) {
        gfx2.PutPixel(endX - 1, y, borderColor);
        gfx2.PutPixel(endX - 2, y, borderColor);
    }
}

void Drawin::DrawBoardFrame(Color c)
{
    //not used in code, to delete

	// Clip the frame coordinates to screen bounds
	//int startX = std::max(0, Board::BoardStartY - Graphics::BoardFrameWidth);
	//int startY = std::max(0, Board::BoardStartY - Graphics::BoardFrameWidth);
    //int endX = std::min(Graphics::ScreenWidth - 1, Board::BoardEndX);// +Graphics::BoardFrameWidth);
    //int endY = std::min(Graphics::ScreenHeight - 1, Board::BoardEndY);// +Graphics::BoardFrameWidth);
	
	// Top frame
	if (Board::BoardStartY >= Graphics::MenuThicknessTop + Graphics::WindowFrameWidth){//Graphics::BoardFrameWidth) {
		for (int y = Board::BoardStartY - Graphics::BoardFrameWidth; y < Board::BoardStartY; y++) {
			if (y >= 0 && y < Graphics::ScreenHeight) {
				for (int x = std::max(0, Board::BoardStartX - Graphics::BoardFrameWidth); 
					 x < std::min(Graphics::ScreenWidth, Board::BoardEndX + Graphics::BoardFrameWidth); x++) {
					SafePutPixel(x, y, c);
				}
			}
		}
	}
	
	// Bottom frame
	if (Board::BoardEndY <= Graphics::ScreenHeight - Graphics::MenuThicknessBottom - Graphics::WindowFrameWidth) {
		for (int y = Board::BoardEndY; y < std::min(Graphics::ScreenHeight, Board::BoardEndY + Graphics::BoardFrameWidth); y++) {
			for (int x = std::max(0, Board::BoardStartX - Graphics::BoardFrameWidth); 
				 x < std::min(Graphics::ScreenWidth, Board::BoardEndX + Graphics::BoardFrameWidth); x++) {
				SafePutPixel(x, y, c);
			}
		}
	}
	
	// Left frame
	if (Board::BoardStartX >= Graphics::MenuThicknessLeft + Graphics::WindowFrameWidth) {
		for (int x = Board::BoardStartX - Graphics::BoardFrameWidth; x < Board::BoardStartX; x++) {
			if (x >= 0 && x < Graphics::ScreenWidth) {
				for (int y = std::max(0, Board::BoardStartY - Graphics::BoardFrameWidth); 
					 y < std::min(Graphics::ScreenHeight, Board::BoardEndY + Graphics::BoardFrameWidth); y++) {
					SafePutPixel(x, y, c);
				}
			}
		}
	}
	
	// Right frame
	if (Board::BoardEndX < Graphics::ScreenWidth - Graphics::BoardFrameWidth) {
		for (int x = Board::BoardEndX; x < std::min(Graphics::ScreenWidth, Board::BoardEndX + Graphics::BoardFrameWidth); x++) {
			for (int y = std::max(0, Board::BoardStartY - Graphics::BoardFrameWidth); 
				 y < std::min(Graphics::ScreenHeight, Board::BoardEndY + Graphics::BoardFrameWidth); y++) {
				SafePutPixel(x, y, c);
			}
		}
	}
}

void Drawin::DrawWindowFrame(Color c)
{
    // Clip to screen boundaries - this is almost always within bounds 
    // but better safe than sorry

    // Top frame
    for (int y = 0; y < Graphics::WindowFrameWidth && y < Graphics::ScreenHeight; y++)
    {
        for (int x = 0; x < Graphics::ScreenWidth; x++)
        {
            SafePutPixel(x, y, c);
        }
    }
    
    // Bottom frame
    for (int y = std::max(0, Graphics::ScreenHeight - Graphics::WindowFrameWidth); y < Graphics::ScreenHeight; y++)
    {
        for (int x = 0; x < Graphics::ScreenWidth; x++)
        {
            SafePutPixel(x, y, c);
        }
    }
    
    // Left frame
    for (int x = 0; x < Graphics::WindowFrameWidth && x < Graphics::ScreenWidth; x++)
    {
        for (int y = 0; y < Graphics::ScreenHeight; y++)
        {
            SafePutPixel(x, y, c);
        }
    }
    
    // Right frame
    for (int x = std::max(0, Graphics::ScreenWidth - Graphics::WindowFrameWidth); x < Graphics::ScreenWidth; x++)
    {
        for (int y = 0; y < Graphics::ScreenHeight; y++)
        {
            SafePutPixel(x, y, c);
        }
    }
}