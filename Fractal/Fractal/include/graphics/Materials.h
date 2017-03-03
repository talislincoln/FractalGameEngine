#ifndef MATERIALS_H
#define MATERIALS_H
#include <vector>
#include <Fractal\include\graphics\Texture.h>
namespace fractal {
	namespace fgraphics {
		class Materials {
		public:

			//virtual 
			void bindMaterial();
		private:

		protected:

			std::vector<Texture> m_textures;

		};
	}
}
#endif // !MATERIALS_H
