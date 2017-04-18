#include "graphics\materials\DefaultSkyboxMaterial.h"

namespace fractal {
	namespace fgraphics {

		DefaultSkyboxMaterial::DefaultSkyboxMaterial() : Material(
			new ShaderProgram(DEFAULT_SKYBOX_SHADER, DEFAULT_SKYBOX_SHADER, 1, "position"))
		{
			m_uniforms.push_back(new UniformMatrix("projectionMatrix"));     //0
			m_uniforms.push_back(new UniformMatrix("viewMatrix"));           //1
			m_uniforms.push_back(new UniformSampler("cubeMap"));
			m_shader->storeUniformLocations(m_uniforms);

			std::string files[] = { DEFAULT_SKYBOX_TEXTURE_RIGHT, DEFAULT_SKYBOX_TEXTURE_LEFT, DEFAULT_SKYBOX_TEXTURE_TOP,
				DEFAULT_SKYBOX_TEXTURE_BOTTOM, DEFAULT_SKYBOX_TEXTURE_BACK, DEFAULT_SKYBOX_TEXTURE_FRONT };

			loadCubemap(files, 6);
		}

		void fractal::fgraphics::DefaultSkyboxMaterial::loadCubemap(std::string* textureFiles, int numOfFiles)
		{
			GLuint texID;

			glGenTextures(1, &texID);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

			for (int i = 0; i < numOfFiles; i++) {
				TextureData* textureData = LoadTexture::decodeTexturePNG(textureFiles[i]);

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, textureData->getWidth(), textureData->getHeight(), 0, GL_RGBA,
					GL_UNSIGNED_BYTE, &(textureData->getBuffer()[0]));

				delete textureData;
			}
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			
			///maybe this is leaking memory for the textures created in OPENGL!!!!!
			textureID = texID;
		}
	}
}