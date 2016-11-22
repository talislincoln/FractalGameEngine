#include "PhysicsShape.h"

namespace fractal {
	namespace fphysics {



		PhysicsShape::PhysicsShape(float friction, float restitution, float density)
		{
			this->friction = friction;
			this->restitution = restitution;
			this->density = density;
		}


		PhysicsShape::~PhysicsShape()
		{
		}

	}
}