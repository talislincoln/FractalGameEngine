#ifndef _PHYSICS_WORLD_H
#define _PHYSICS_WORLD_H
#include <vector>
#include "core\systems\System.h"
#include "scene\Component.h"
#include <FractalPhysics\PhysicsShape.h>
#include <FractalPhysics\PhysicsMath.h>
namespace fractal {
	namespace fcore {

		class PhysicsWorld : public System
		{
		public:
			PhysicsWorld();
			virtual ~PhysicsWorld();

		private:

			std::vector<fscene::Component> colliderList;
			std::vector<fscene::Component> bodyList;

			friend class PhysicsBodyComponent;
			friend class PhysicsShapeComponent;
		};
	}
}

#endif // !_PHYSICS_WORLD_H