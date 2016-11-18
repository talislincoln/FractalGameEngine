#ifndef _PHYSICS_BODY_COMPONENT
#define _PHYSICS_BODY_COMPONENT

#include <Fractal\include\scene\Component.h>
#include <FractalPhysics\include\PhysicsBody.h>
namespace fractal {
	namespace fphysics {
		struct DefaultBody;
		//class defaultBox;
		//struct Box;
		class PhysicsBodyComponent :
			public fscene::Component
		{
		public:
			PhysicsBodyComponent();
			virtual ~PhysicsBodyComponent();
			bool initialize();
			void update();
			bool shutdown();
		private:
			PhysicsBody* body;
			const fscene::GameObject* parent;
			friend class PhysicsBody;
			friend class PhysicsShapeComponent;
		};
	}
}

#endif // !_BODY_COMPONENT