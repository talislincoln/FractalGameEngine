#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include <Fractal\include\scene\Component.h>
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\graphics\MeshData.h>
#include "graphics\materials\DefaultMeshMaterial.h"

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
			void createVAO();
			void storeDataInVAO();
			void unbindVAO() const;
			void bindIndicesBuffer();

			size_t m_indicesSize, m_vecticesSize;
			fgraphics::MeshData* m_mesh;
			fgraphics::Material* m_material;

			GLuint m_vao;

			//list of vertices to be deleted from the gpu
			//std::vector<GLuint> m_vaos;
			std::vector<GLuint> m_vbos;
		};
	}
}

#endif // !_MESHCOMPONENT_H
