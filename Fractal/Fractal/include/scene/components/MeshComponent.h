#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include <Fractal\include\scene\Component.h>
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\graphics\MeshData.h>
#include "graphics\materials\DefaultMeshMaterial.h"
#include "graphics\vao.h"
namespace fractal {
	namespace fscene {
		class TransformComponent;
		using namespace fmath;
		class MeshComponent : public Component, public IDrawable {
		public:
			MeshComponent(fgraphics::MeshData* mesh, fgraphics::Material* m = new fgraphics::DefaultMaterial());
			virtual ~MeshComponent();

			virtual bool initialize();
			virtual void draw();
			virtual void update();
			virtual bool shutdown();
			inline void setMaterial(fractal::fgraphics::Material* m) {
				m_material = m;
			}
		private:
			fgraphics::Material* m_material;
			fgraphics::Vao* m_vao;
		};
	}
}

#endif // !_MESHCOMPONENT_H
