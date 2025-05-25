#include "GraphicMode.h"

void GraphicMode::DrawBackground(Drawin drw) {

}

void GraphicMode::DrawForeground(Drawin drw) {

}
void GraphicMode::SwitchDarkMode() {
	darkmode = !darkmode;
	if (darkmode)
		GraphicMode::bgColor = Colors::DarkBackGround;
	else
		GraphicMode::bgColor = Colors::LightBackGround;
}