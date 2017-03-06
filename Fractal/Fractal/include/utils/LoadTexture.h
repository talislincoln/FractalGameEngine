#ifndef LOAD_TEXTURE_H
#define LOAD_TEXTURE_H
#include <string>
#include <fstream>
#include <vector>
#include <GL\glew.h>
namespace fractal {
	namespace fgraphics {
		class Texture;
		class TextureBuilder;
		class TextureData;
		struct LoadTexture {
			
			LoadTexture() = delete;
			LoadTexture(const LoadTexture&) = delete;
			LoadTexture(LoadTexture&&) = delete;
			LoadTexture& operator=(const LoadTexture&) = delete;
			LoadTexture& operator=(LoadTexture&&) = delete;

			static void loadFile(std::vector<unsigned char>& buffer, const std::string& filename);
			static TextureData decodeTexturePNG(std::string& reader);
			static GLuint loadTextureToOpenGL(TextureData& data, TextureBuilder& Builder);

		};
	}
}

#endif // !LOAD_TEXTURE_H
