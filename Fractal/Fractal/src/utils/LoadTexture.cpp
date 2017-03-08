#include "utils\LoadTexture.h"

#include <iostream>
#include <assert.h>

#include <Fractal\include\utils\picoPNG.h>
#include <Fractal\include\utils\TextureBuilder.h>
#include <Fractal\include\graphics\Texture.h>
#include <Fractal\include\utils\IOManager.h>
namespace fractal {
	namespace fgraphics {



		TextureData* LoadTexture::decodeTexturePNG(const std::string& reader)
		{
			std::string path = "res/" + reader + ".png";
			unsigned long width = 0;
			unsigned long height = 0;
			std::vector<unsigned char> buffer, image;
			if (IOManager::readFileToBuffer(path, buffer) == false) {
				std::cout << ("fail loading png file" + path);
			}

			int error = PicoPNG::decodePNG(image, width, height, &buffer[0], buffer.size());
			if (error != 0)
				std::cout << ("Tried to load texture " + path + " , didn't work");

			return new TextureData(width, height, image);
		}

		GLuint LoadTexture::loadTextureToOpenGL(TextureData* data, TextureBuilder& builder)
		{
			GLuint textureID;
			glGenTextures( 1, &textureID);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->getWidth(), data->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, &(data->getBuffer()[0]));
			if (builder.isMipmap()) {
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				GLfloat max;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);
				if (builder.isAnisotropic() && max > 0) {
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
					glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
				}
			}
			else if (builder.isNearest()) {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
			if (builder.isClampEdges()) {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
			return textureID;
		}
	}
}
