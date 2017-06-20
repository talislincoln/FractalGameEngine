#include "core\resources\TextureResource.h"
#include "utils\IOManager.h"

#include "utils\picoPNG.h"

#include <iostream>

namespace fractal {
	namespace fcore {
		namespace fresource {
			TextureResource::TextureResource(const std::string& resourcePath) :
				Resource(resourcePath, ResourceType::TEXTURE_RESOURCE),
				m_width(0), m_height(0)
			{
				glGenTextures(1, &m_id);

				m_clampEdges = false;
				m_mipMap = false;
				m_anisotropic = true;
				m_nearest = false;
			}

			TextureResource::~TextureResource() {

			}

			bool TextureResource::initialize() {
				loadTextureToOpenGL(decodeTexturePNG());

				return true;
			}

			bool TextureResource::shutdown() {
				glDeleteBuffers(1, &m_id);
			}

			std::vector<unsigned char> TextureResource::decodeTexturePNG()
			{
				//std::string path = "res/" + reader + ".png";
				//unsigned long width = 0;
				//unsigned long height = 0;
				std::vector<unsigned char> buffer, image;
				if (IOManager::readFileToBuffer(m_resourcePath, buffer) == false) {
					std::cout << ("fail loading png file " + m_resourceName);
				}

				int error = PicoPNG::decodePNG(image, m_width, m_height, &buffer[0], buffer.size());
				if (error != 0)
					std::cout << ("Tried to load texture " + m_resourceName + ", didn't work");

				return image;
			}

			//GLuint TextureResource::loadTextureToOpenGL(TextureData* data, TextureBuilder& builder)
			void TextureResource::loadTextureToOpenGL(std::vector<unsigned char> imageBuffer)
			{
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, m_id);
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(imageBuffer[0]));
				if (m_mipMap) {
					glGenerateMipmap(GL_TEXTURE_2D);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
					GLfloat max;
					glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &max);
					if (m_anisotropic && max > 0) {
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0);
						glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4.0f);
					}
				}
				else if (m_nearest) {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				}
				else {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				}
				if (m_clampEdges) {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				}
				else {
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				}
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}
	}
}