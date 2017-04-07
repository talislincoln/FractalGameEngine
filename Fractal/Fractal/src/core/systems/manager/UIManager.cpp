#include "core\systems\manager\UIManager.h"
using namespace fractal;
using namespace fcore;
fractal::fcore::UIManager::UIManager()
{
}

fractal::fcore::UIManager::~UIManager()
{
}

bool fractal::fcore::UIManager::initialize()
{
	return false;
}

bool fractal::fcore::UIManager::shutdown()
{
	return false;
}

std::multimap<unsigned int, IUserInterface*>& fractal::fcore::UIManager::getUIList()
{
	return m_UIList;
}

void fractal::fcore::UIManager::addUiList(unsigned int depth, IUserInterface* UIComponent)
{
	if(UIComponent != nullptr)
		m_UIList.insert(std::pair<unsigned int, IUserInterface*>(depth, UIComponent));
}
