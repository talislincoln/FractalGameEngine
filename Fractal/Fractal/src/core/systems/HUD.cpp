#include "core\systems\HUD.h"
#include <GL\glew.h>
#include "core\systems\manager\UIManager.h"
#include "helpers\Singleton.h"
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
	beginDraw();
	std::multimap<unsigned int, IUserInterface*>::iterator it;
	for (it = fhelpers::Singleton<UIManager>::getInstance().getUIList().begin(); it != fhelpers::Singleton<UIManager>::getInstance().getUIList().end(); ++it) {
		if (it->second->getUICanDraw())
			it->second->draw2D();
	}
	endDraw();
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
