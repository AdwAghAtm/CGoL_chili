#include "Visuals.h"
#include <array>

bool Visuals::darkmode = true;
Color Visuals::bgColor = Colors::DarkBackGround;
Color Visuals::netColor = Colors::DarkGray2;
GraphicMode Visuals::currentVisual = GraphicMode::Alt4; //set default visual effect

void Visuals::DrawBackground(Drawing* drw) {
	drw->DrawBackground(bgColor);
	
	if (currentVisual>= Legacy1 && currentVisual <= Legacy4)
		drw->DrawNet(netColor);
	else
		drw->DrawNetAlt(netColor);
}

void Visuals::DrawForeground(std::array<bool, 9> neighbors, int x, int y, Drawing* drw) {
	drw->DrawSquare(x, y, Colors::CoalChan);

	switch ((static_cast<int>(Visuals::currentVisual)) % 4 + 1) {
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

void Visuals::SwitchDarkMode() {
	darkmode = !darkmode;
	if (darkmode) {
		Visuals::bgColor = Colors::DarkBackGround;
		Visuals::netColor = Colors::DarkGray2;
	}
	else {
		Visuals::bgColor = Colors::LightBackGround;
		Visuals::netColor = Colors::LightGray;
	}
}

void Visuals::SwitchVisuals() {
	Visuals::currentVisual = static_cast<GraphicMode>((static_cast<int>(Visuals::currentVisual) + 1) % 8);
}