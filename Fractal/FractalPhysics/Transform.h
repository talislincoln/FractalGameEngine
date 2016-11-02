#pragma once
#include "Component.h"
#include <FractalMath\Math.h>
namespace fractal {
	class Transform : Component
	{
	public:
		Transform(fmath::Point3 transform, fmath::Point3 rotate, fmath::Point3 scale);
		~Transform();

	};
}
