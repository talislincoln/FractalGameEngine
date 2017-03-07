#ifndef MATERIALS_H
#define MATERIALS_H
#include <vector>
#include <Fractal\include\graphics\Texture.h>
#include <Fractal\include\graphics\ShaderProgram.h>
namespace fractal {
	namespace fgraphics {
		class Materials {
		public:
			Materials(ShaderProgram* Shader): m_shader(Shader) {}
			//virtual 
			virtual void bindMaterial();
			virtual void unbindMaterial();
			virtual void use();
			virtual void unuse();
			virtual void destroy();
		private:

		protected:

			std::vector<Texture*> m_textures;
			ShaderProgram* m_shader;

		};
	}
}
#endif // !MATERIALS_H
