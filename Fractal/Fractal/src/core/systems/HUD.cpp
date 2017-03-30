#include "core\systems\HUD.h"
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
