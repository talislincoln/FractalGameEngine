#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include <Fractal\include\graphics\Mesh.h>
#include <Fractal\include\defines\Colour.h>
#include <Fractal\include\scene\Component.h>
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\graphics\Program.h>

namespace fractal {
	namespace fscene {
		class TransformComponent;
		using namespace fmath;
		class MeshComponent : public Component, public IDrawable {
		public:
			MeshComponent(fgraphics::Mesh* mesh);
			virtual ~MeshComponent();

			virtual bool initialize();
			virtual void draw();
			virtual void update();
			virtual bool shutdown();

			inline fgraphics::Mesh* getMesh() const {
				return m_mesh;
			}
		private:
			void createVAO();
			void storeDataInVAO();
			void unbindVAO();

			fgraphics::Mesh* m_mesh;

			GLuint m_vao;
			GLuint m_vbo;
			GLuint m_ebo;

			//list of vertices to be deleted from the gpu
			std::vector<GLuint> m_vaos;
			std::vector<GLuint> m_vbos;
		};
	}
}

#endif // !_MESHCOMPONENT_H
