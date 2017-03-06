#ifndef MATERIALS_H
#define MATERIALS_H
#include <vector>
#include <Fractal\include\graphics\Texture.h>
#include <Fractal\include\graphics\ShaderProgram.h>
namespace fractal {
	namespace fgraphics {
		class Materials {
		public:

			//virtual 
			virtual void bindMaterial();
			virtual void use();
			virtual void unuse();
			virtual void destroy();
		private:

		protected:

			std::vector<Texture*> m_textures;
			ShaderProgram* Shader;

		};
	}
}
#endif // !MATERIALS_H
