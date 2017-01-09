#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include <Fractal\include\scene\Component.h>


#include <FractalMath\Quaternion.h>
#include <FractalPhysics\include\Transform.h>
namespace fractal {
	namespace fscene {
		class TransformComponent : public Component
		{
		public:
			TransformComponent(const std::string& name = "");
			virtual ~TransformComponent();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			void translate(const fmath::Vector3& translation);
			void scale(const fmath::Vector3& scale);
			void rotate(const fmath::Quaternion& rotation);

			// ***** setters and getters ***** //

			inline void TransformComponent::setPosition(const fmath::Vector3& position) {
				this->m_isDirty = true;
				this->m_physicsChanges = true;
				this->m_position = position;
			}
			inline void TransformComponent::setPosition(float x, float y, float z) {
				setPosition(fmath::Vector3(x, y, z));
			}

			inline void TransformComponent::setScale(const fmath::Vector3& scale) {
				this->m_isDirty = true;
				this->m_physicsChanges = true;
				this->m_scaling = scale;
			}

			inline void TransformComponent::setRotation(const fmath::Quaternion q) {
				this->m_isDirty = true;
				this->m_physicsChanges = true;
				this->m_rotation = q;
			}
			inline const fmath::Vector3& getPosition() const {
				return m_position;
			}
			
			inline const fmath::Vector3& getScale() const {
				return m_scaling;
			}

			inline const fmath::Quaternion& getRotation() const {
				return m_rotation;
			}

			inline const fmath::Matrix4& getWorldMatrix() const {
				return m_worldMatrix;
			}

			inline fphysics::Transform getPhysicsTransform() {
				return fphysics::Transform(this->m_position, this->m_rotation, this->m_scaling);
			}
			inline TransformComponent& operator = (const fphysics::Transform& p)
			{
				this->m_position = p.position;
				this->m_rotation = p.rotation;
				this->m_scaling = p.scale;
				return *this;
			}
			inline bool getPhysicsChanges() {
				return m_physicsChanges;
			}
			inline void donePhysicsChange() {
				m_physicsChanges = false;
			}
		private:
			bool m_isDirty;
			bool m_physicsChanges;

			fmath::Vector3 m_position;
			fmath::Vector3 m_scaling;
			fmath::Quaternion m_rotation;

			fmath::Matrix4 m_worldMatrix;
		};
	}
}

#endif // !_TRANSFORMCOMPONENT_H
