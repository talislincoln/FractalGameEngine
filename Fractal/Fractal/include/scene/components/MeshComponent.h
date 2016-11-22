#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include "graphics\Mesh.h"
#include "defines\Colour.h"
#include "scene\Component.h"
#include "interfaces\IDrawable.h"
#include "graphics\Program.h"

namespace fractal {
	namespace fscene {
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
			fgraphics::Mesh* m_mesh;

			GLuint m_vbo;
			GLuint m_vao;
			GLuint m_ebo;
			//;w; window dimensions
			const GLuint WIDTH = 800;
			const GLuint HEIGHT = 600;
			std::vector<fgraphics::Vertex> vertices;
			GLuint vertices2;
			//;w; shader stuff
			Shader* m_ourProgram;
			//;w; textures
			GLuint m_texture1;
			GLuint m_texture2;
			int IMG_WIDTH, IMG_HEIGHT;
			unsigned char* m_image;
			//;w; other
		};
	}
}

#endif // !_MESHCOMPONENT_H
