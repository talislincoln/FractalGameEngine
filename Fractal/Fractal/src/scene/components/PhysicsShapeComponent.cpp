#include "scene/components/PhysicsShapeComponent.h"

#include "scene\components\PhysicsBodyComponent.h"

#include "scene\components\TransformComponent.h"

#include <Fractal\include\scene\GameObject.h>

namespace fractal {
	namespace fphysics {
		PhysicsShapeComponent::PhysicsShapeComponent(PhysicsShape* shapeDef, const std::string& name) :
			Component(name == "" ? "PhysicsShapeComponent" : name)
		{
			shape = shapeDef;
			initialize();
			//std::vector<fmath::Point3> temp = shapeDef->getVertices();
			//for (int i = 0; i < temp.size(); i++) {
			//	//vertices.push_back(temp[i]);
			//}

		}


		PhysicsShapeComponent::~PhysicsShapeComponent()
		{
		}
		bool PhysicsShapeComponent::initialize() {
			parent = this->getParent();
			if (parent != nullptr) {
				body = parent->getComponent<PhysicsBodyComponent>();//have to find the first body from parent tree, todo list
				transform = parent->getComponent<fscene::TransformComponent>();
			}
			//shape->localPosition = parent->getTranform(); todo list.
			if (body == nullptr) {
				//no body, no mass , center of mass, etc. 
			}
			else {
				body->m_checkMass = true;
				body->shapes.push_back(shape);
				// has *at least one body* 
				//body->m_body->calculateMassData();
				//body->   getaabb;
			}
			return true;
		}
		bool PhysicsShapeComponent::shutdown() {
			delete shape;
			return true;
		}
		void PhysicsShapeComponent::update() {
			if (parent == nullptr) {
				parent = this->getParent();
				if (parent != nullptr) {
					body = parent->getComponent<PhysicsBodyComponent>();//have to find the first body from parent tree, todo list
					transform = parent->getComponent<fscene::TransformComponent>();
				}
				//shape->localPosition = parent->getTranform(); todo list.
				if (body == nullptr) {
					//no body, no mass , center of mass, etc. 
				}
				else {
					body->m_checkMass = true;
					body->shapes.push_back(shape);
					// has *at least one body* 
					//body->m_body->calculateMassData();
					//body->   getaabb;
				}
			}
		}
		void PhysicsShapeComponent::draw() const {
			transform->getWorldMatrix();
			vertices;
		}
	}
}
