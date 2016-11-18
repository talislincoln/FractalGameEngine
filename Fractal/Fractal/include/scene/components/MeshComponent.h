#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include "graphics\Mesh.h"
#include "defines\Colour.h"
#include "scene\Component.h"
#include "interfaces\IDrawable.h"

namespace fractal {
	namespace fscene {
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
			//window dimensions
			const GLuint WIDTH = 800;
			const GLuint HEIGHT = 600;
			std::vector<fgraphics::Vertex> vertices;
			std::vector<fgraphics::Vertex> vertices2;

			/*const GLchar* vertexShaderSource = "#version 330 core\n"
				"layout (location = 0) in vec3 position;\n"
				"void main()\n"
				"{\n"
				"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
				"}\0";
			const GLchar* fragmentShaderSource = "#version 330 core\n"
				"out vec4 color;\n"
				"void main()\n"
				"{\n"
				"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\n\0";
			GLuint shaderProgram;*/
		};
	}
}

#endif // !_MESHCOMPONENT_H
