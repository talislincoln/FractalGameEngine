#include "graphics\materials\DefaultMeshMaterial.h"
namespace fractal {
	namespace fgraphics {

		DefaultMaterial::DefaultMaterial() : Material(new ShaderProgram(DEFAULT_SHADER, DEFAULT_SHADER,
			3, "position", "normal", "texCoord")) {
			m_uniforms.push_back(new UniformMatrix("view"));            //0
			m_uniforms.push_back(new UniformMatrix("projection"));      //1
			m_uniforms.push_back(new UniformMatrix("model"));           //2
			m_uniforms.push_back(new UniformVector3("lightDirection")); //3
			m_uniforms.push_back(new UniformSampler("diffuseMap"));     //4
			//need to setup texture so i can use DefaultMaterial and just add textures
			m_textures.push_back(Texture::newTexture(DEFAULT_TEXTURE).anisotropic().create());
			m_shader->storeUniformLocations(m_uniforms);
			loadTexture();
		}

		void fractal::fgraphics::DefaultMaterial::loadTexture()
		{
			static_cast<UniformSampler*>(m_uniforms[4])->loadTextureUnit(m_textures[0]->TEXTUREID);
		}


	}
}