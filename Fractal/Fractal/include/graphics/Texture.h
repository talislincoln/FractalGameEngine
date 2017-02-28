#ifndef TEXTURE_H
#define TEXTURE_H

#include <sstream>
#include <vector>
#include <GL\glew.h>
#include <Fractal\include\utils\LoadTexture.h>
#include <Fractal\include\utils\TextureBuilder.h>
namespace fractal {
	namespace fgraphics {

		class Texture {
		public:
			const int TEXTUREID;
			const int SIZE;

			Texture(int Id, int size, GLint type = GL_TEXTURE_2D) : TEXTUREID(Id), SIZE(size), TYPE(type) {}


		private:
			const GLint TYPE;
		};


		class TextureData {
		private:
			int m_width;
			int m_height;
			std::vector<unsigned char> m_buffer;
		public:
			inline TextureData(int width, int height, std::vector<unsigned char>& buffer) : m_width(width), m_height(height), m_buffer(buffer) {}
			inline int getWidth() {
				return m_width;
			}
			inline int getHeight() {
				return m_height;
			}
			inline std::vector<unsigned char> getBuffer() {
				return m_buffer;
			}
		};
	}
}

#endif // !TEXTURE_H
