#pragma once
#include "Drawin.h"
//#include "Colors.h"


class GraphicMode
{
public:
	static void DrawBackground(Drawin drw);
	static void DrawForeground(Drawin drw);
	static void SwitchDarkMode();
private:
	static bool darkmode;
	static Color bgColor;
};