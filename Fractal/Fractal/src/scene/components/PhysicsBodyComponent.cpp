#include "scene/components/PhysicsBodyComponent.h"

namespace fractal {
	namespace fphysics {
		PhysicsBodyComponent::PhysicsBodyComponent() {
			parent = this->getParent();
			//body->getParentTransform(this->getTransform());
		}
		PhysicsBodyComponent::~PhysicsBodyComponent()
		{
		}

		bool PhysicsBodyComponent::initialize() {
			return true;
		}
		void PhysicsBodyComponent::update() {

		}
		bool PhysicsBodyComponent::shutdown() {
			return true;
		}

	}
}
