#include "graphics\materials\DefaultUIMaterial.h"
#include <FractalMath\Matrix.h>
namespace fractal {
	namespace fgraphics {

		DefaultUIMaterial::DefaultUIMaterial() : Material(new ShaderProgram(DEFAULT_UI_SHADER, DEFAULT_UI_SHADER,
			1, "position")) {
			m_uniforms.push_back(new UniformMatrix("transformationMatrix"));           //0
			m_uniforms.push_back(new UniformSampler("UITexture"));      //1           
			//need to setup texture so i can use DefaultUIMaterial and just add textures
			m_textures.push_back(Texture::newTexture(DEFAULT_TEXTURE).anisotropic().create());
			m_shader->storeUniformLocations(m_uniforms);
			loadTexture();
		}


		void fractal::fgraphics::DefaultUIMaterial::loadTexture()
		{
			static_cast<UniformSampler*>(m_uniforms[1])->loadTextureUnit(m_textures[0]->TEXTUREID);
		}
	}
}