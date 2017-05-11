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
			virtual void draw() const;

			virtual bool initialize();
			virtual bool shutdown();

			void beginDraw() const;
			void endDraw() const;
		};
	}
}
#endif // !HUD_H
