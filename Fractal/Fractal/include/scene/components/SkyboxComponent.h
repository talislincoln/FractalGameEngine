#ifndef _SKYBOX_COMPONENT_H
#define _SKYBOX_COMPONENT_H

#include <Fractal\include\graphics\Vao.h>
#include <Fractal\include\scene\Component.h>
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\graphics\materials\DefaultSkyboxMaterial.h>

namespace fractal {
	namespace fscene {

		class CameraComponent;

		class SkyboxComponent : public Component, public IDrawable{
		public:
			SkyboxComponent(fgraphics::Material* m = new fgraphics::DefaultSkyboxMaterial());
			~SkyboxComponent();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			virtual void draw() const;

		private:
			fgraphics::Material* m_material;
			fgraphics::Vao* m_vao;

			CameraComponent* m_camera;
		};
	}
}

#endif // !_SKYBOX_COMPONENT_H