#include "scene/components/PhysicsBodyComponent.h"
#include "scene\components\TransformComponent.h"
#include <Fractal\include\scene\GameObject.h>
#include "core\systems\PhysicsWorld.h"
#include "helpers\Singleton.h"
#include "core\systems\manager\SystemManager.h"

namespace fractal {
	namespace fphysics {
		PhysicsBodyComponent::PhysicsBodyComponent(PhysicsBody* bodyDef, const std::string& name) :
			Component(name == "" ? "PhysicsBodyComponent" : name), m_body(bodyDef), m_isGround(false),
			m_checkMass(false){
			m_body = bodyDef;

			//body->getParentTransform(this->getTransform());
		}
		PhysicsBodyComponent::~PhysicsBodyComponent()
		{
		}

		bool PhysicsBodyComponent::initialize() {
			physicsWorld = dynamic_cast<PhysicsWorld*>(fhelpers::Singleton<fcore::SystemManager>::getInstance().getSystem(SystemType::PHYSICS_SYSTEM));
			parent = this->getParent();
			if (parent == nullptr) {}
			else {
				physicsWorld->gameOjbectWithBodyList.push_back(this->getParent());//grandparent?
				transform = parent->getComponent<fscene::TransformComponent>();
				//m_physicsTransform = transform->getPhysicsTransform(); // copy + future watch list for muti parents
			}
			return true;
		}
		void PhysicsBodyComponent::update() {
			if (m_checkMass) {
				m_body->calculateMassData(shapes, transform->getPhysicsTransform());
				m_checkMass = false;
			}
			if (transform->getPhysicsChanges()) {
				m_body->m_aabb = AABB();
				for (auto& shape : shapes) {
					shape->setAABB(transform->getPhysicsTransform(), &m_body->m_aabb);
				}
			}

			transform->donePhysicsChange();
		}
		bool PhysicsBodyComponent::shutdown() {
			delete m_body;
			return true;
		}

	}
}
