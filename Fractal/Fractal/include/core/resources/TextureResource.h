#ifndef _TEXTURERESOURCE_H
#define _TEXTURERESOURCE_H

#include <string>
#include <vector>
#include "core\resources\Resource.h"

namespace fractal {
	namespace fcore {
		namespace fresource {
			class TextureResource : public Resource {
			public:
				TextureResource(const std::string& resourcePath);
				~TextureResource();

				virtual bool initialize();
				virtual bool shutdown();
			private:

				std::vector<unsigned char> decodeTexturePNG();
				void loadTextureToOpenGL(std::vector<unsigned char> imageBuffer);

				unsigned long m_width;
				unsigned long m_height;

				bool m_clampEdges;
				bool m_mipMap;
				bool m_anisotropic;
				bool m_nearest;
			};
		}
	}
}
#endif // !_TEXTURERESOURCE_H
