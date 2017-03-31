#include "core\systems\HUD.h"
#include <GL\glew.h>
using namespace fractal;
using namespace fcore;

HUD::HUD() : System(SystemType::HUD_SYSTEM)
{
}

void HUD::update()
{
}

void HUD::draw()
{
}

bool HUD::initialize()
{
	return true;
}

bool HUD::shutdown()
{
	return true;
}

void HUD::beginDraw()
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}

void HUD::endDraw()
{
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}
