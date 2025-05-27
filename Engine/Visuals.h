#pragma once
#include "Drawing.h"

enum GraphicMode {
	Legacy1,
	Legacy2,
	Legacy3,
	Legacy4,
	Alt1,
	Alt2,
	Alt3,
	Alt4
};

class Visuals
{
public:
	static void DrawBackground(Drawing* drw);
	static void DrawForeground(std::array<bool, 9> neighbors, int x, int y, Drawing* drw);
	static void SwitchDarkMode();
	static void SwitchVisuals();
private:
	static bool darkmode;
	static Color bgColor;
	static Color netColor;
	static GraphicMode currentVisual;
};