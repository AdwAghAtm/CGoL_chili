#pragma once
#include "Drawin.h"

enum Visuals {
	Legacy1,
	Legacy2,
	Legacy3,
	Legacy4,
	Alt1,
	Alt2,
	Alt3,
	Alt4
};

class GraphicMode
{
public:
	static void DrawBackground(Drawin* drw);
	static void DrawForeground(std::array<bool, 9> neighbors, int x, int y, Drawin* drw);
	static void SwitchDarkMode();
	static void SwitchVisuals();
private:
	static bool darkmode;
	static Color bgColor;
	static Color netColor;
	static Visuals currentVisual;
};