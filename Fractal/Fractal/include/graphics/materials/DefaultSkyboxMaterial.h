#ifndef _DEFAULTSKYBOXMATERIAL_H
#define _DEFAULTSKYBOXMATERIAL_H
#include "graphics\Material.h"
#include <GL\glew.h>
namespace fractal {
	namespace fgraphics {

#define DEFAULT_SKYBOX_SHADER "Defaults/Materials/Shaders/DefaultSkybox"

// these textures has to be give in the right order!
#define DEFAULT_SKYBOX_TEXTURE_RIGHT "Defaults/Materials/Skyboxes/right"
#define DEFAULT_SKYBOX_TEXTURE_LEFT "Defaults/Materials/Skyboxes/left"
#define DEFAULT_SKYBOX_TEXTURE_TOP "Defaults/Materials/Skyboxes/top"
#define DEFAULT_SKYBOX_TEXTURE_BOTTOM "Defaults/Materials/Skyboxes/bottom"
#define DEFAULT_SKYBOX_TEXTURE_BACK "Defaults/Materials/Skyboxes/back"
#define DEFAULT_SKYBOX_TEXTURE_FRONT "Defaults/Materials/Skyboxes/front"

		class DefaultSkyboxMaterial : public Material {
		public:
			DefaultSkyboxMaterial();
		private:
			virtual void loadTexture();

			static const float SIZE;
			static const float VERTICES[];
		};

		const float DefaultSkyboxMaterial::SIZE = 500.0f;

		const float DefaultSkyboxMaterial::VERTICES[] = {
			-SIZE,  SIZE, -SIZE,
			-SIZE, -SIZE, -SIZE,
			SIZE, -SIZE, -SIZE,
			SIZE, -SIZE, -SIZE,
			SIZE,  SIZE, -SIZE,
			-SIZE,  SIZE, -SIZE,

			-SIZE, -SIZE,  SIZE,
			-SIZE, -SIZE, -SIZE,
			-SIZE,  SIZE, -SIZE,
			-SIZE,  SIZE, -SIZE,
			-SIZE,  SIZE,  SIZE,
			-SIZE, -SIZE,  SIZE,

			SIZE, -SIZE, -SIZE,
			SIZE, -SIZE,  SIZE,
			SIZE,  SIZE,  SIZE,
			SIZE,  SIZE,  SIZE,
			SIZE,  SIZE, -SIZE,
			SIZE, -SIZE, -SIZE,

			-SIZE, -SIZE,  SIZE,
			-SIZE,  SIZE,  SIZE,
			SIZE,  SIZE,  SIZE,
			SIZE,  SIZE,  SIZE,
			SIZE, -SIZE,  SIZE,
			-SIZE, -SIZE,  SIZE,

			-SIZE,  SIZE, -SIZE,
			SIZE,  SIZE, -SIZE,
			SIZE,  SIZE,  SIZE,
			SIZE,  SIZE,  SIZE,
			-SIZE,  SIZE,  SIZE,
			-SIZE,  SIZE, -SIZE,

			-SIZE, -SIZE, -SIZE,
			-SIZE, -SIZE,  SIZE,
			SIZE, -SIZE, -SIZE,
			SIZE, -SIZE, -SIZE,
			-SIZE, -SIZE,  SIZE,
			SIZE, -SIZE,  SIZE
		};
	}
}
#endif // !_DEFAULTSKYBOXMATERIAL_H
