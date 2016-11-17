#include "scene/components/PhysicsShapeComponent.h"



namespace fractal {
	namespace fphysics {
		PhysicsShapeComponent::PhysicsShapeComponent(PhysicsShape* shapeDef)
		{
			parent = this->getParent();
			body = parent->getComponent<PhysicsBodyComponent>();
			shape = shapeDef;
			//shape->localPosition = parent->getTranform(); todo list.
			if (body == nullptr) {
				//no body, no mass , center of mass, etc. 
			}
			else {
				// has *at least one body* 
				body->calculateMassData();
				//body->   getaabb;
			}
		}


		PhysicsShapeComponent::~PhysicsShapeComponent()
		{
		}
		bool PhysicsShapeComponent::shutdown() {
			return true;
		}
	}
}
