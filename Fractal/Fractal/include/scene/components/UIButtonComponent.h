#ifndef UI_BUTTONCOMPONENT_H
#define UI_BUTTONCOMPONENT_H

#include "UIComponent.h"
#include "interfaces\IInput.h"
namespace fractal {
	namespace fHUD {
		class UIButtonComponent : public UIComponent , public IMouseInput {
		public:
			UIButtonComponent();
			virtual ~UIButtonComponent();
			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();
			virtual void draw2D();
			virtual void setupMouseInput(fcore::Input* input);
		private:
			void mouseMotion(const fmath::Vector2& mouseCoord);
			void mouseClick(const fmath::Vector2& mouseCoord);
		};
	}
}


#endif // !UIBUTTONCOMPONENT_H
