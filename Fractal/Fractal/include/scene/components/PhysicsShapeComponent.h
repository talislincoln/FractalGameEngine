#ifndef _SHAPE_COMPONENT
#define _SHAPE_COMPONENT
#include <Fractal\include\scene\GameObject.h>
#include <Fractal\include\scene\Component.h>
#include <FractalMath\Matrix.h>
#include <FractalPhysics\include\collision\AABB.h>
#include <FractalPhysics\include\Transform.h>
#include <FractalPhysics\include\shapes\PhysicsShape.h>
#include <FractalPhysics\include\PhysicsDefine.h>
#include <FractalPhysics\include\PhysicsBody.h>
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
			PhysicsBody* body;
			friend class PhysicsWorld;
		};
	}
}
#endif // !_SHAPE_COMPONENT
