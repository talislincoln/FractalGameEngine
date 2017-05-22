#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H
#include "graphics\Light.h"
namespace fractal {
	namespace fgraphics {
		class DirectionLight : public Light {
		public:
			DirectionLight(const fmath::Vector3& direction = fmath::Vector3(1.0f, 0.0f, 0.0f), 
				const fmath::Vector3& m = fmath::Vector3(), const fmath::Vector3& d = fmath::Vector3(), const fmath::Vector3& s = fmath::Vector3());
		};
	}
}
#endif