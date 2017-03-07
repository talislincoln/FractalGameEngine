#include "utils\TextureBuilder.h"

#include <Fractal\include\utils\LoadTexture.h>

#include <Fractal\include\graphics\Texture.h>
namespace fractal {
	namespace fgraphics {
		TextureBuilder::TextureBuilder(const char* filePath) : m_file(filePath) {

			m_clampEdges = false;
			m_mipMap = false;
			m_anisotropic = true;
			m_nearest = false;
		}

		TextureBuilder::~TextureBuilder()
		{
		}

		Texture* TextureBuilder::create()
		{
			TextureData* textureData = LoadTexture::decodeTexturePNG(m_file);
			int textureId = LoadTexture::loadTextureToOpenGL(textureData, *this);
			int width = textureData->getWidth();

			delete textureData;
			return new Texture(textureId, width);
		}


	}
}
