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
	}
}
#endif // !_SHAPE
