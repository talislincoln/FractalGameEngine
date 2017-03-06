#include "utils\LoadTexture.h"

#include <iostream>
#include <assert.h>

#include <Fractal\include\utils\picoPNG.h>
#include <Fractal\include\utils\TextureBuilder.h>
#include <Fractal\include\graphics\Texture.h>

namespace fractal {
	namespace fgraphics {


		void LoadTexture::loadFile(std::vector<unsigned char>& buffer, const std::string& filename) //designed for loading files from hard disk in an std::vector
		{
			std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

			//get filesize
			std::streamsize size = 0;
			if (file.seekg(0, std::ios::end).good()) size = file.tellg();
			if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

			//read contents of the file into the vector
			if (size > 0)
			{
				buffer.resize((size_t)size);
				file.read((char*)(&buffer[0]), size);
			}
			else buffer.clear();
		}

		TextureData LoadTexture::decodeTexturePNG(std::string& reader)
		{
			unsigned int width = 0;
			unsigned int height = 0;
			std::vector<unsigned char> buffer, image;
			loadFile(buffer, reader);

			int error = PicoPNG::decodePNG(image, width, height, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());
			if (error != 0)
				std::cout << ("Tried to load texture " + reader + " , didn't work");

			return TextureData(width, height, buffer);
		}

		GLuint LoadTexture::loadTextureToOpenGL(TextureData& data, TextureBuilder& builder)
		{
			GLuint textureID;
			glGenTextures( 1, &textureID);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.getWidth(), data.getHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, &(data.getBuffer()[0]));
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
