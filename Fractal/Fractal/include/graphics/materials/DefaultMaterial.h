#ifndef DEFAULTMATERIAL_H
#define DEFAULTMATERIAL_H
#include "graphics\Material.h"
#include <GL\glew.h>
namespace fractal {
	namespace fgraphics {

#define DEFAULT_SHADER "Defaults/Materials/Shaders/DefaultShader"
#define DEFAULT_TEXTURE "Defaults/Materials/Textures/defaultTexture"
		class DefaultMaterial : public Material {
		public:
			DefaultMaterial();
		private:
			void loadTexture();
		};
	}
}
#endif // !DefaultMaterial_H
