#ifndef _SHAPE_COMPONENT
#define _SHAPE_COMPONENT
#include <Fractal\include\scene\GameObject.h>
#include <Fractal\include\scene\Component.h>
#include <FractalMath\Matrix.h>
#include <FractalPhysics\AABB.h>
#include <FractalPhysics\Transform.h>
#include <FractalPhysics\PhysicsShape.h>
#include <FractalPhysics\PhysicsDefine.h>
#include "PhysicsBodyComponent.h"
#include <vector>
namespace fractal {
	namespace fphysics {
		class PhysicsBodyComponent;
		class PhysicsShapeComponent : public fscene::Component
		{
		public:
			PhysicsShapeComponent(PhysicsShape* shapeDef);
			~PhysicsShapeComponent();

			bool shutdown();
		private:
			//PhysicsShapeComponent* next;
			PhysicsShape* shape;
			const fscene::GameObject* parent;
			PhysicsBodyComponent* body;

		};
	}
}
#endif // !_SHAPE_COMPONENT
