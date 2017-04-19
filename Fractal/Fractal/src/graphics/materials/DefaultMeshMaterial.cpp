#include "graphics\materials\DefaultMeshMaterial.h"
namespace fractal {
	namespace fgraphics {

		DefaultMaterial::DefaultMaterial() : Material(
			new ShaderProgram(DEFAULT_SHADER, DEFAULT_SHADER,
			3, "position", "normal", "texCoord")) 
		{
			m_uniforms.push_back(new UniformMatrix("view"));            //0
			m_uniforms.push_back(new UniformMatrix("projection"));      //1
			m_uniforms.push_back(new UniformMatrix("model"));           //2
			m_uniforms.push_back(new UniformVector3("viewPos"));        //3
			m_uniforms.push_back(new UniformSampler("material.diffuse"));	//4
			m_uniforms.push_back(new UniformSampler("material.specular"));	//5
			m_uniforms.push_back(new UniformFloat("material.luster"));	//6
			//;w; testing stuff
			m_uniforms.push_back(new UniformVector3("light.ambient"));	//7
			m_uniforms.push_back(new UniformVector3("light.diffuse"));	//8
			m_uniforms.push_back(new UniformVector3("light.specular"));	//9
			m_uniforms.push_back(new UniformFloat("light.constant"));	//10
			m_uniforms.push_back(new UniformFloat("light.linear"));		//11
			m_uniforms.push_back(new UniformFloat("light.quadratic"));	//12
			m_uniforms.push_back(new UniformVector3("light.direction"));//13

			//m_uniforms.push_back(new UniformVector3("lightDirection")); //6
			//need to setup texture so i can use DefaultMaterial and just add textures
			m_textures.push_back(Texture::newTexture(DEFAULT_TEXTURE).anisotropic().create());
			m_textures.push_back(Texture::newTexture(DEFAULT_TEXTURE).anisotropic().create());
			m_shader->storeUniformLocations(m_uniforms);
			loadTexture();
		}

		void fractal::fgraphics::DefaultMaterial::loadTexture()
		{
			static_cast<UniformSampler*>(m_uniforms[4])->loadTextureUnit(m_textures[0]->TEXTUREID);
			static_cast<UniformSampler*>(m_uniforms[5])->loadTextureUnit(m_textures[1]->TEXTUREID);
		}
	}
}