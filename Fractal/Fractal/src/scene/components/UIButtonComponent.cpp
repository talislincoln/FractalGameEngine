#include "scene\components\UIButtonComponent.h"
#include "helpers\Singleton.h"
#include "core\systems\manager\SystemManager.h"

fractal::fHUD::UIButtonComponent::UIButtonComponent() : fractal::fHUD::UIComponent()
{
}

fractal::fHUD::UIButtonComponent::~UIButtonComponent()
{
}

bool fractal::fHUD::UIButtonComponent::initialize()
{
	static_cast<fcore::Input*>(fhelpers::Singleton<fcore::SystemManager>::getInstance().getSystem(SystemType::INPUT_SYSTEM))->addInputComponent(this);
	return UIComponent::initialize();
}

void fractal::fHUD::UIButtonComponent::update()
{
	UIComponent::update();
}

bool fractal::fHUD::UIButtonComponent::shutdown()
{
	return UIComponent::shutdown();;
}

void fractal::fHUD::UIButtonComponent::draw2D()
{
	UIComponent::draw2D();
}

void fractal::fHUD::UIButtonComponent::setupInput(fcore::Input* input)
{
	printf("i am here");
	using namespace std::placeholders;

	input->bindInput(fcore::MouseBinding(SDLK_LEFT, std::bind(&UIButtonComponent::mouseMotion, this, _1), InputStateType::MOUSE_MOTION));
	input->bindInput(fcore::MouseBinding(SDL_BUTTON_LEFT, std::bind(&UIButtonComponent::mouseClick, this, _1), InputStateType::MOUSE_PRESSED));
}

void fractal::fHUD::UIButtonComponent::mouseMotion(const fmath::Vector2 & mouseCoord)
{
}

void fractal::fHUD::UIButtonComponent::mouseClick(const fmath::Vector2 & mouseCoord)
{
}
