#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "graphics\Light.h"
namespace fractal {
	namespace fgraphics {
		class PointLight : public Light {
		public: 
			PointLight(const fmath::Vector3& m = fmath::Vector3(), const fmath::Vector3& d = fmath::Vector3(), const fmath::Vector3& s = fmath::Vector3());
		};
	}
}
#endif