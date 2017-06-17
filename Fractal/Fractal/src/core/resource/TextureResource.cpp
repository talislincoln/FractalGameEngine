#include "core\resources\TextureResource.h"

namespace fractal {
	namespace fcore {
		namespace fresource {
			TextureResource::TextureResource(const std::string& resourcePath) :
				Resource(resourcePath, ResourceType::TEXTURE_RESOURCE)
			{
				glGenTextures(1, &m_id);
			}

			TextureResource::~TextureResource() {

			}

			bool TextureResource::initialize() {

			}

			bool TextureResource::shutdown() {

			}
		}
	}
}