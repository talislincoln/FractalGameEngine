#include "core\systems\PhysicsWorld.h"

#include "scene\components\PhysicsBodyComponent.h"
#include "scene\components\TransformComponent.h"
#include "scene\components\PhysicsShapeComponent.h"
#include "scene\components\TerrainComponent.h"
#include <FractalPhysics\include\PhysicsMath.h>
#include <FractalPhysics\include\collision\AABBCollision.h>
#include <Fractal\include\core\systems\Timer.h>
#include <helpers\Singleton.h>
#include <Fractal\include\core\systems\manager\SystemManager.h>

namespace fractal {
	namespace fphysics {
		PhysicsWorld::PhysicsWorld(const fmath::Vector3 gravity) :
			System(SystemType::PHYSICS_SYSTEM), m_gravity(gravity),
			m_allowSleep(true), m_enableFriction(true), collided(true) {
		}


		bool PhysicsWorld::initialize() {
			return true;

		}
		bool PhysicsWorld::shutdown() {
			return true;
		}

		void PhysicsWorld::update() {
			simulation();
			checkCollision();

			//SDL_Delay(timer.GetSleepTime(60));
		}
		void PhysicsWorld::destroy() {

		}
		void PhysicsWorld::simulation() {
			using namespace fhelpers;
			int i = 0;
			dtime = dynamic_cast<fcore::Timer*>(fhelpers::Singleton<fcore::SystemManager>::getInstance().getSystem(SystemType::TIMER_SYSTEM))->deltaTime;
			//dtime = timer.GetDeltaTime() / 2.0f;
			for (auto& body : gameOjbectWithBodyList) {

				//VelocityState *vState = m_velocities + ++i; // for collidion with reaction. 

				fphysics::PhysicsBodyComponent* physicsBody = body->getComponent<fphysics::PhysicsBodyComponent>();
				if (physicsBody == nullptr) {
					//REMOVE THIS BODY FROM THE LIST.
				}
				if (!physicsBody->IsAwake())
					continue;
				fscene::TransformComponent* transform = body->getComponent<fscene::TransformComponent>();

				if (physicsBody->m_body->m_flags & PhysicsBody::DYNAMIC)
				{
					physicsBody->ApplyLinearForce(m_gravity * physicsBody->m_body->m_gravityScale);
					
					// Calculate world space intertia tensor
					fmath::Matrix3 r = transform->getRotation().toMatrix3();
					physicsBody->m_body->m_inverseInertiaWorld = r * physicsBody->m_body->m_inverseInertiaModel * Matrix3::transpose(r);

					// Integrate velocity
					physicsBody->m_body->m_linearVelocity += (physicsBody->m_body->m_force * physicsBody->m_body->m_inverseMass) * dtime;
					physicsBody->m_body->m_angularVelocity += (physicsBody->m_body->m_inverseInertiaWorld * physicsBody->m_body->m_torque) * dtime;

					//physicsBody->m_body->m_linearVelocity *= float(1.0) / (float(1.0) + dtime * physicsBody->m_body->m_linearDamping);
					//physicsBody->m_body->m_angularVelocity *= float(1.0) / (float(1.0) + dtime * physicsBody->m_body->m_angularDamping);
				}


				//vState->v = physicsBody->m_body->m_linearVelocity;
				//vState->w = physicsBody->m_body->m_angularVelocity;

				physicsBody->m_body->m_worldCenter += physicsBody->m_body->m_linearVelocity * dtime;
				//transform->setPosition(physicsBody->m_body->m_worldCenter);
				physicsBody->m_body->m_quaternion.integrate(physicsBody->m_body->m_angularVelocity, dtime);
				transform->setRotation(physicsBody->m_body->m_quaternion);
				transform->setPosition(physicsBody->m_body->m_worldCenter);

				if (physicsBody->m_body->m_worldCenter.y < terrain->getHeight(transform->getPosition())) {
					physicsBody->setGround(true);
					fmath::Point3 temp = transform->getPosition();
					physicsBody->m_body->m_worldCenter.y = terrain->getHeight(temp);
					transform->setPosition(physicsBody->m_body->m_worldCenter);
					float tempps = physicsBody->getFriction();
					physicsBody->m_body->m_linearVelocity *= physicsBody->getFriction();
					physicsBody->m_body->m_angularVelocity *=physicsBody->getFriction();

					if (physicsBody->m_body->m_linearVelocity.y < 0) {
						physicsBody->m_body->m_linearVelocity.y = 0;
					}
				}
				else {
					physicsBody->setGround(false);
				}
				//AHHHH ;w;
				physicsBody->reset();
			}

			if (m_allowSleep)
			{
				// Find minimum sleep time of the entire island
				float minSleepTime = MAX_FLOAT;
				for (auto& body : gameOjbectWithBodyList) {
					fphysics::PhysicsBodyComponent* physicsBody = body->getComponent<fphysics::PhysicsBodyComponent>();
					if (physicsBody->GetFlags() & PhysicsBody::STATIC)
						continue;

					const float sqrLinVel = physicsBody->GetLinearVelocity().dot(physicsBody->GetLinearVelocity());
					const float cbAngVel = physicsBody->GetAngularVelocity().dot(physicsBody->GetAngularVelocity());
					const float linTol = SLEEP_LINEAR;
					const float angTol = SLEEP_ANGULAR;

					if (sqrLinVel > linTol || cbAngVel > angTol)
					{
						minSleepTime = float(0.0);
						physicsBody->m_body->m_sleepTime = float(0.0);
					}
					else
					{
						physicsBody->m_body->m_sleepTime += dtime;
						minSleepTime = fmath::getMin(minSleepTime, physicsBody->m_body->m_sleepTime);
					}
					if (physicsBody->m_body->m_sleepTime > 5.0) {
						physicsBody->SetToSleep();
					}
				}
				/*
				if (minSleepTime > SLEEP_TIME)
				{
					for (auto& body : gameOjbectWithBodyList) {
						fphysics::PhysicsBodyComponent* physicsBody = body->getComponent<fphysics::PhysicsBodyComponent>();
						physicsBody->SetToSleep();
					}
				}
				island imp. not done yet. but it's here.*/
			}
		}
		bool PhysicsWorld::checkCollision() {
			for (unsigned int i = 0; i < gameOjbectWithBodyList.size(); i++) {
				for (unsigned int j = i + 1; j < gameOjbectWithBodyList.size(); j++) {
					if (fphysics::AABBCollision::isCollide(gameOjbectWithBodyList[i]->getComponent<PhysicsBodyComponent>()->m_body->m_aabb, 
						gameOjbectWithBodyList[j]->getComponent<PhysicsBodyComponent>()->m_body->m_aabb)) {
						//printf("collided");
						//if aabb pass. do more checking..
						reaction(gameOjbectWithBodyList[i], gameOjbectWithBodyList[j]);

					}

				}
			}

					
			return true;
		}
		void PhysicsWorld::reaction(fscene::GameObject* a, fscene::GameObject* b) {
			if (collided) {
				a->getComponent<PhysicsBodyComponent>()->SetLinearVelocity(-a->getComponent<PhysicsBodyComponent>()->GetLinearVelocity());
				b->getComponent<PhysicsBodyComponent>()->SetLinearVelocity(-b->getComponent<PhysicsBodyComponent>()->GetLinearVelocity());
				collided = false;
			}
		}
		void PhysicsWorld::setTerrainComponent(fscene::TerrainComponent* terrain) {
			this->terrain = terrain;
		}
	}
}