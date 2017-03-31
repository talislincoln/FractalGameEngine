#ifndef HUD_H
#define HUD_H
#include "System.h"
#include "interfaces\IDrawable.h"
namespace fractal {
	namespace fcore {
		class HUD : public System, public IDrawable {
		public:
			HUD();
			virtual void update();
			virtual void draw();

			virtual bool initialize();
			virtual bool shutdown();

			void beginDraw();
			void endDraw();
		};
	}
}
#endif // !HUD_H
