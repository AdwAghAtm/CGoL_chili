#pragma once
#include "Drawin.h"

class GraphicMode
{
public:
	static void DrawBackground(Drawin* drw);
	static void DrawForeground(std::array<bool, 9> neighbors, int x, int y, Drawin* drw);
	static void SwitchDarkMode();
private:
	static bool darkmode;
	static Color bgColor;
};