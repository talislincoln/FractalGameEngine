#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "graphics\Light.h"
namespace fractal {
	namespace fgraphics {
		class SpotLight : public Light {
		public:
			SpotLight(const fmath::Vector3& m = fmath::Vector3(), const fmath::Vector3& d = fmath::Vector3(), const fmath::Vector3& s = fmath::Vector3());
		};
	}
}

#endif // !SPOTLIGHT_H
