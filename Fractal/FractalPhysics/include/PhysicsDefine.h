#ifndef _SHAPE
#define _SHAPE

namespace fractal {
	namespace fphysics {
		enum Shape {
			BOX,
			SPHERE,
			CAPSULE,
			PLANE
		};
		enum BodyType
		{
			STATICBODY,
			DYNAMICBODY,
			KINEMATICBODY
		};

		struct massData
		{
			fmath::Matrix3 inertia;
			fmath::Vector3 center;
			float mass;
		};
	}
}
#endif // !_SHAPE
