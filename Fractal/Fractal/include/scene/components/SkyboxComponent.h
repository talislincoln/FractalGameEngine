#ifndef _SKYBOX_COMPONENT_H
#define _SKYBOX_COMPONENT_H

#include <Fractal\include\interfaces\IDrawable.h>
//13:50

namespace fractal {
	namespace fscene {
		class SkyboxComponent : public Component, public IDrawable {
		public:
			SkyboxComponent(fgraphics::Material* m = new fgraphics::DefaultSkyboxMaterial());
			~SkyboxComponent();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			virtual void draw();

		private:

		};
	}
}

#endif // !_SKYBOX_COMPONENT_H