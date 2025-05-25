#include "GraphicMode.h"
#include <array>

bool GraphicMode::darkmode = true;
Color GraphicMode::bgColor = Colors::DarkBackGround;

void GraphicMode::DrawBackground(Drawin* drw) {
	drw->DrawBackground(bgColor);
	drw->DrawNetAlt(Colors::DarkGray2);
}

void GraphicMode::DrawForeground(std::array<bool, 9> neighbors, int x, int y, Drawin* drw) {

}
void GraphicMode::SwitchDarkMode() {
	darkmode = !darkmode;
	if (darkmode)
		GraphicMode::bgColor = Colors::DarkBackGround;
	else
		GraphicMode::bgColor = Colors::LightBackGround;
}