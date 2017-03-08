#ifndef MATERIALS_H
#define MATERIALS_H
#include <vector>
#include <Fractal\include\graphics\Texture.h>
#include <Fractal\include\graphics\ShaderProgram.h>

namespace fractal {
	namespace fgraphics {
		class Material {
		public:
			Material(ShaderProgram* Shader): m_shader(Shader) {}
			//virtual 
			virtual void use();
			virtual void unuse();
			virtual void destroy();
			virtual void loadCamera(const fmath::Matrix4& view,const fmath::Matrix4& projection,const fmath::Matrix4& model); // need to set up default one for all material
		protected:
			std::vector<Uniform*> m_uniforms;
			std::vector<Texture*> m_textures;
			ShaderProgram* m_shader;

		};
	}
}
#endif // !Materials_H
