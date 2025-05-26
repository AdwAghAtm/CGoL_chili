#include "GraphicMode.h"
#include <array>

bool GraphicMode::darkmode = true;
Color GraphicMode::bgColor = Colors::DarkBackGround;
Color GraphicMode::netColor = Colors::DarkGray2;
Visuals GraphicMode::currentVisual = Visuals::Alt4; //set default visual effect

void GraphicMode::DrawBackground(Drawing* drw) {
	drw->DrawBackground(bgColor);
	
	if (currentVisual>= Legacy1 && currentVisual <= Legacy4)
		drw->DrawNet(netColor);
	else
		drw->DrawNetAlt(netColor);
}

void GraphicMode::DrawForeground(std::array<bool, 9> neighbors, int x, int y, Drawing* drw) {
	drw->DrawSquare(x, y, Colors::CoalChan);

	switch ((static_cast<int>(GraphicMode::currentVisual)) % 4 + 1) {
	case 1:
		break;
	case 2:
		drw->DrawSurroundings(neighbors, x, y, Colors::CoalChan);
		break;
	case 3:
		drw->DrawOuterCorners(x, y, Colors::CoalChan, bgColor);
		break;
	case 4:
		drw->DrawSurroundings(neighbors, x, y, Colors::CoalChan);
		drw->DrawInnerCorners(neighbors, x, y, Colors::CoalChan);
		drw->DrawOuterCorners(neighbors, x, y, Colors::CoalChan, bgColor);
		break;
	default:
		break;
	}
}

void GraphicMode::SwitchDarkMode() {
	darkmode = !darkmode;
	if (darkmode) {
		GraphicMode::bgColor = Colors::DarkBackGround;
		GraphicMode::netColor = Colors::DarkGray2;
	}
	else {
		GraphicMode::bgColor = Colors::LightBackGround;
		GraphicMode::netColor = Colors::LightGray;
	}
}

void GraphicMode::SwitchVisuals() {
	GraphicMode::currentVisual = static_cast<Visuals>((static_cast<int>(GraphicMode::currentVisual) + 1) % 8);
}