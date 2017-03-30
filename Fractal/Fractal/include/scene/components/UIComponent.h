#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H
#include "scene\Component.h"

namespace fractal {
	namespace fHUD {
		class UIComponent : public fscene::Component {
			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();
		};
	}
}
#endif // !UI_COMPONENT_H
