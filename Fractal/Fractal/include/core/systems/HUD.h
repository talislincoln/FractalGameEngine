#ifndef HUD_H
#define HUD_H
#include "System.h"
#include "interfaces\IDrawable.h"
namespace fractal {
	namespace fcore {
		class HUD : public System, public IDrawable {
		public:
			HUD();
			void update();
			void destroy();

			bool initialize();
			bool shutdown();

		};
	}
}
#endif // !HUD_H
