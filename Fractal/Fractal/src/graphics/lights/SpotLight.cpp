#include "graphics\lights\SpotLight.h"
namespace fractal {
	namespace fgraphics {
		SpotLight::SpotLight(const fmath::Vector3 & m, const fmath::Vector3 & d, const fmath::Vector3 & s)
			: Light(LightType::SPOT_LIGHT, m, d, s)
		{
		}
	}
}