#ifndef MATERIALS_H
#define MATERIALS_H

#ifndef DEFALUT_TEXTURE
#define DEFAULT_TEXTURE "Defaults/Materials/Textures/defaultTexture"
#endif // !DEFALUT_TEXTURE
#include <vector>
#include <Fractal\include\graphics\Texture.h>
#include <Fractal\include\graphics\ShaderProgram.h>

namespace fractal {
	namespace fscene {
		class LightComponent;
	}

	namespace fgraphics {
		class Material {
		public:
			Material(ShaderProgram* Shader) : m_shader(Shader) {}
			//virtual 
			virtual void use();
			virtual void unuse();
			virtual void destroy();
			virtual void loadCamera(const fmath::Matrix4& view, const fmath::Matrix4& projection, const fmath::Matrix4& model);
			virtual void loadProjectionMatrix(const fmath::Matrix4& projection);
			virtual void loadViewMatrix(const fmath::Matrix4& view);
			// need to set up default one for all material
			virtual void load2DMatrix(const fmath::Vector2& t = fmath::Vector2(), float rolate = 0, const fmath::Vector2& scale = fmath::Vector2(1), int index = 0);
			virtual void loadNewTexture(Texture* newTexture, const unsigned int location = 0);
			virtual void loadTransform(const fmath::Matrix4& TransformMatrix, unsigned int location = 0);

			/// Loads the default values for a light
			virtual void loadLight(const fmath::Vector3& lightPos, const fmath::Vector3& lightColour);
			//;w; test
			virtual void loadProperties(const fmath::Vector3& viewPos);
			virtual void loadMaterial(const float materialDiffuse, const float materialSpecular, const float materialLuster);
			virtual void loadDirectional(const fmath::Vector3& direction, const fmath::Vector3& ambient, const fmath::Vector3& diffuse, const fmath::Vector3& specular);
			virtual void loadPoint(const fmath::Vector3& position, const fmath::Vector3& ambient, const fmath::Vector3& diffuse, const fmath::Vector3& specular, const float& constant, const float& linear, const float& quadratic);
			virtual void loadSpot(const fmath::Vector3& position, const fmath::Vector3& direction, const fmath::Vector3& ambient, const fmath::Vector3& diffuse, const fmath::Vector3& specular, const float& constant, const float& linear, const float& quadratic, const float& cutoff, const float& outerCutoff);
			/// Loads the default values for the "shineness" of a material
			/// The numbers 6 and 7 are set as default based on the index position for the array at the DefaultMeshMaterial.
			virtual void loadShineVariables(float damper, float reflectivity, int damperIndex = 6, int reflectivityIndex = 7);

			virtual void loadTexture() = 0;

			inline void setShineDamper(float sd) {
				m_shineDamper = sd;
			}

			inline float getShineDamper() const {
				return m_shineDamper;
			}

			inline void setReflectivity(float r) {
				m_reflectivity = r;
			}

			inline float getReflectivity() const {
				return m_reflectivity;
			}
		protected:
			// should use map 
			std::vector<Uniform*> m_uniforms;
			std::vector<Texture*> m_textures;
			ShaderProgram* m_shader;

			float m_shineDamper = 5.0f;
			float m_reflectivity = 1.0f;
		};
	}
}
#endif // !Materials_H
