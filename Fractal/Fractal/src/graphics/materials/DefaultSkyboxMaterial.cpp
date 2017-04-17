#include "graphics\materials\DefaultSkyboxMaterial.h"

namespace fractal {
	namespace fgraphics {

		DefaultSkyboxMaterial::DefaultSkyboxMaterial() : Material(
			new ShaderProgram(DEFAULT_SKYBOX_SHADER, DEFAULT_SKYBOX_SHADER, 1, "position"))
		{
			m_uniforms.push_back(new UniformMatrix("projectionMatrix"));     //1
			m_uniforms.push_back(new UniformMatrix("viewMatrix"));           //2

			m_textures.push_back(Texture::newTexture(DEFAULT_TEXTURE).anisotropic().create());
			m_shader->storeUniformLocations(m_uniforms);

			loadTexture();
		}

		void fractal::fgraphics::DefaultSkyboxMaterial::loadTexture()
		{
			//static_cast<UniformSampler*>(m_uniforms[m_shader->getUniformLocation("diffuseMap")])->loadTextureUnit(m_textures[0]->TEXTUREID);

		}
	}
}