#ifndef _TEXTURERESOURCE_H
#define _TEXTURERESOURCE_H

#include <string>
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
				unsigned int m_width;
				unsigned int m_height;
			};
		}
	}
}
#endif // !_TEXTURERESOURCE_H
