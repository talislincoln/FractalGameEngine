#ifndef _MESHCOMPONENT_H
#define _MESHCOMPONENT_H

#include <Fractal\include\graphics\Mesh.h>
#include <Fractal\include\defines\Colour.h>
#include <Fractal\include\scene\Component.h>
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\graphics\shaders\MeshShader.h>
#include <Fractal\include\graphics\MeshData.h>
#include <Fractal\include\graphics\Texture.h>

namespace fractal {
	namespace fscene {
		class TransformComponent;
		using namespace fmath;
		class MeshComponent : public Component, public IDrawable {
		public:
			MeshComponent(fgraphics::MeshData* mesh);
			virtual ~MeshComponent();

			virtual bool initialize();
			virtual void draw();
			virtual void update();
			virtual bool shutdown();

			inline fgraphics::MeshData* getMesh() const {
				return m_mesh;
			}
		private:
			void createVAO();
			void storeDataInVAO();
			void unbindVAO() const;
			void bindIndicesBuffer();
			size_t m_indicesSize, m_vecticesSize;
			fgraphics::MeshData* m_mesh;
			fgraphics::MeshShader* m_shader;
			fgraphics::Texture* m_texture;// Materials in the future. just need to test it here.
			GLuint m_vao;

			//list of vertices to be deleted from the gpu
			std::vector<GLuint> m_vaos;
			std::vector<GLuint> m_vbos;
		};
	}
}

#endif // !_MESHCOMPONENT_H
