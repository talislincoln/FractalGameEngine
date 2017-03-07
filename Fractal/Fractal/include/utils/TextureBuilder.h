#ifndef TEXTURE_BUILDER_H
#define TEXTURE_BUILDER_H
#include <fstream>
#include <string>
namespace fractal {
	namespace fgraphics {
		class Texture; // forward 
		class TextureData;
		class TextureBuilder {
		private:
			bool m_clampEdges;
			bool m_mipMap;
			bool m_anisotropic;
			bool m_nearest;
			std::string m_file;
		public:
			TextureBuilder(const char* filePath);
			~TextureBuilder();
			Texture* create();

			inline TextureBuilder clampEdges() {
				m_clampEdges = true;
				return *this;
			}

			inline TextureBuilder normalMipMap() {
				m_mipMap = true;
				m_anisotropic = false;
				return *this;
			}

			inline TextureBuilder nearestFiltering() {
				m_mipMap = false;
				m_anisotropic = false;
				m_nearest = true;
				return *this;
			}

			inline TextureBuilder anisotropic() {
				m_mipMap = true;
				m_anisotropic = true;
				return *this;
			}

			inline bool isClampEdges() {
				return m_clampEdges;
			}

			inline bool isMipmap() {
				return m_mipMap;
			}

			inline bool isAnisotropic() {
				return m_anisotropic;
			}

			inline bool isNearest() {
				return m_nearest;
			}
		};
	}
}
#endif // !TEXTURE_BUILDER_H
