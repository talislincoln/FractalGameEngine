#ifndef LIGHT_H
#define LIGHT_H
// Struct to store lighst's information. helps with loading materials.
// need improvement too!
#include <FractalMath\Math.h>

namespace fractal {
	namespace fgraphics {
		class Light {
		public:
			enum class LightType {
				POINT_LIGHT,
				DIRECTION_LIGHT,
				SPOT_LIGHT
			};
			inline Light(LightType flag, const fmath::Vector3& m = fmath::Vector3(), const fmath::Vector3& d = fmath::Vector3(), const fmath::Vector3& s = fmath::Vector3()) {
				m_flags = flag;
				m_ambient = m;
				m_diffuse = d;
				m_specular = s;
			}
			inline void setAmbient(const fmath::Vector3& m) {
				m_ambient = m;
			}
			inline void setDiffuse(const fmath::Vector3& d) {
				m_diffuse = d;
			}
			inline void setSpecular(const fmath::Vector3& s) {
				m_specular = s;
			}
			inline const fmath::Vector3& getAmbient() const {
				return m_ambient;
			}
			inline const fmath::Vector3& getDiffuse() const {
				return m_diffuse;
			}
			inline const fmath::Vector3& getSpecular() const {
				return m_specular;
			}
			inline LightType getFlags() const {
				return m_flags;
			}
		private:
			fmath::Vector3 m_ambient;
			fmath::Vector3 m_diffuse;
			fmath::Vector3 m_specular;
		protected:
			LightType m_flags;
		};
	}
}
#endif // !LIGHT_H
