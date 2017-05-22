#include "graphics\materials\DefaultMeshMaterial.h"
namespace fractal {
	namespace fgraphics {

		DefaultMaterial::DefaultMaterial() : Material(
			new ShaderProgram(DEFAULT_SHADER, DEFAULT_SHADER,
				3, "position", "normal", "texCoord"))
		{
			m_uniforms.push_back(new UniformMatrix("view"));				//0
			m_uniforms.push_back(new UniformMatrix("projection"));			//1
			m_uniforms.push_back(new UniformMatrix("model"));				//2
			m_uniforms.push_back(new UniformVector3("viewPos"));			//3
			m_uniforms.push_back(new UniformSampler("material.diffuse"));	//4
			m_uniforms.push_back(new UniformSampler("material.specular"));	//5
			m_uniforms.push_back(new UniformFloat("material.luster"));		//6
			//;w; directional light
			m_uniforms.push_back(new UniformVector3("dirlight.direction"));	//7
			m_uniforms.push_back(new UniformVector3("dirlight.ambient"));	//8
			m_uniforms.push_back(new UniformVector3("dirlight.diffuse"));	//9
			m_uniforms.push_back(new UniformVector3("dirlight.specular"));	//10
			//;w; point light
			m_uniforms.push_back(new UniformVector3("pointlight.position"));//11
			m_uniforms.push_back(new UniformVector3("pointlight.ambient"));	//12
			m_uniforms.push_back(new UniformVector3("pointlight.diffuse"));	//13
			m_uniforms.push_back(new UniformVector3("pointlight.specular"));//14
			m_uniforms.push_back(new UniformFloat("pointlight.constant"));	//15
			m_uniforms.push_back(new UniformFloat("pointlight.linear"));	//16
			m_uniforms.push_back(new UniformFloat("pointlight.quadratic"));	//17
			//;w; spot light
			m_uniforms.push_back(new UniformVector3("spotlight.position"));	//18
			m_uniforms.push_back(new UniformVector3("spotlight.direction"));//19
			m_uniforms.push_back(new UniformVector3("spotlight.ambient"));	//20
			m_uniforms.push_back(new UniformVector3("spotlight.diffuse"));	//21
			m_uniforms.push_back(new UniformVector3("spotlight.specular"));	//22
			m_uniforms.push_back(new UniformFloat("spotlight.constant"));	//23
			m_uniforms.push_back(new UniformFloat("spotlight.linear"));		//24
			m_uniforms.push_back(new UniformFloat("spotlight.quadratic"));	//25
			m_uniforms.push_back(new UniformFloat("spotlight.cutoff"));		//26
			m_uniforms.push_back(new UniformFloat("spotlight.outerCutoff"));//27
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