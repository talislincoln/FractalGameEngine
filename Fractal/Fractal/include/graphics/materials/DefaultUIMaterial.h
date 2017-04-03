#ifndef DEFAULTUIMATERIAL_H
#define DEFAULTUIMATERIAL_H
#include "graphics\Material.h"
#include <FractalMath\Math.h>
#include <GL\glew.h>
namespace fractal {
	namespace fgraphics {

#define DEFAULT_UI_SHADER "Defaults/Materials/Shaders/DefaultUIShader"

		class DefaultUIMaterial : public Material {
		public:
			DefaultUIMaterial();
			//virtual void loadCamera(const fmath::Matrix4& view, const fmath::Matrix4& projection, const fmath::Matrix4& model) override {};
			// need to set up default one for all material
		private:
			virtual void loadTexture();
		};
	}
}
#endif // !DefaultMaterial_H
