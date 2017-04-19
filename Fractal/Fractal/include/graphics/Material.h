#ifndef MATERIALS_H
#define MATERIALS_H

#ifndef DEFALUT_TEXTURE
#define DEFAULT_TEXTURE "Defaults/Materials/Textures/defaultTexture"
#endif // !DEFALUT_TEXTURE
#include <vector>
#include <Fractal\include\graphics\Texture.h>
#include <Fractal\include\graphics\ShaderProgram.h>

namespace fractal {
	namespace fscene {
		class LightComponent;
	}

	namespace fgraphics {
		class Material {
		public:
			Material(ShaderProgram* Shader): m_shader(Shader) {}
			//virtual 
			virtual void use();
			virtual void unuse();
			virtual void destroy();
			virtual void loadCamera(const fmath::Matrix4& view,const fmath::Matrix4& projection,const fmath::Matrix4& model);
			// need to set up default one for all material
			virtual void load2DMatrix(const fmath::Vector2& t = fmath::Vector2(), float rolate = 0, const fmath::Vector2& scale = fmath::Vector2(1), int index = 0 );
			virtual void loadNewTexture(Texture* newTexture, const unsigned int location = 0);
			virtual void loadTransform(const fmath::Matrix4& TransformMatrix, unsigned int location = 0);
			virtual void loadLight(const fmath::Vector3& lightPos, const fmath::Vector3& lightColour);
			//;w; test
			virtual void loadTest(const fmath::Vector3& lightAmbient, const fmath::Vector3& lightDiffuse, const fmath::Vector3& lightSpecular,
				const float lightConstant, const float lightLinear, const float lightQuadratic, const float materialDiffuse, const float materialSpecular, const float materialLuster);
			virtual void fractal::fgraphics::Material::loadTest2(const fmath::Vector3& lightPos, const fmath::Vector3& ViewPos );
			virtual void loadTexture() = 0;
		protected:
			std::vector<Uniform*> m_uniforms;
			std::vector<Texture*> m_textures;
			ShaderProgram* m_shader;

		};
	}
}
#endif // !Materials_H
