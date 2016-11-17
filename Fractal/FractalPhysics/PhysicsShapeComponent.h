#ifndef _SHAPE_COMPONENT
#define _SHAPE_COMPONENT
#include <Fractal\include\scene\GameObject.h>
#include <Fractal\include\scene\Component.h>
#include <FractalMath\Matrix.h>
#include "AABB.h"
#include "Transform.h"
#include "PhysicsShape.h"
#include "PhysicsDefine.h"
#include "PhysicsBodyComponent.h"
#include <vector>
namespace fractal {
	namespace fphysics {
		class PhysicsBodyComponent;
		struct massData
		{
			fmath::Matrix3 inertia;
			fmath::Vector3 center;
			float mass;
		};
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
