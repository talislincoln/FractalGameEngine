#ifndef _SHAPE_COMPONENT
#define _SHAPE_COMPONENT
#include <Fractal\include\scene\Component.h>
#include <FractalMath\Matrix.h>
#include <FractalPhysics\include\shapes\PhysicsShape.h>
#include <Fractal\include\core\systems\PhysicsWorld.h>

#include <vector>
#include <Fractal\include\interfaces\IDrawable.h>
#include <Fractal\include\graphics\Vertex.h>

namespace fractal {
	namespace fscene {
		class TransformComponent;
	}
	namespace fphysics {
		class PhysicsBodyComponent;

		class PhysicsShapeComponent : public fscene::Component, public IDrawable
		{
		public:
			PhysicsShapeComponent::PhysicsShapeComponent(PhysicsShape* shapeDef, const std::string& name = "");
			~PhysicsShapeComponent();
			virtual bool initialize();
			virtual void draw() const;
			virtual void update();
			virtual bool shutdown();

		private:
			std::vector<fgraphics::Vertex> vertices;
			PhysicsBodyComponent* body;
			fscene::TransformComponent* transform;
			PhysicsShape* shape;
			const fscene::GameObject* parent;

			friend class PhysicsWorld;
		};
	}
}
#endif // !_SHAPE_COMPONENT
