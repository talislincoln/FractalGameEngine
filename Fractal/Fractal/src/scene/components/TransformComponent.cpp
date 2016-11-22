#include "scene\components\TransformComponent.h"
#include "scene\GameObject.h"

namespace fractal {
	namespace fscene {
		TransformComponent::TransformComponent(const std::string& name) :
			Component(name == "" ? "TransformComponent" : name),
			m_isDirty(false),
			m_position(),
			m_scaling(),
			m_rotation()
		{
			//empty
		}

		TransformComponent::~TransformComponent() {

		}

		bool TransformComponent::initialize() {
			return true;
		}

		void TransformComponent::update() {
			if (!this->m_isDirty)
				return;

			this->world_matrix = fmath::Matrix4::scale(this->m_scaling) *
				(this->m_rotation.toMatrix()) *  
				fmath::Matrix4::translate(this->m_position);

			this->m_isDirty = false;
		}

		bool TransformComponent::shutdown() {
			return true;
		}

		void TransformComponent::translate(const fmath::Vector3& translation) {
			setPosition(getPosition() + translation);

			for (GameObject* obj : getParent()->getChilderen())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->translate(translation);
			}
		}

		void TransformComponent::scale(const fmath::Vector3& scale) {
			setScale(getScale() + scale);

			for (GameObject* obj : getParent()->getChilderen())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->scale(scale);
			}
		}

		void TransformComponent::rotate(const fmath::Quaternion rotation) {
			setRotation(getRotation() * rotation);

			for (GameObject* obj : getParent()->getChilderen())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->rotate(rotation);
			}
		}

		void TransformComponent::setPosition(const fmath::Vector3& position) {
			this->m_isDirty = true;
			this->m_position = position;
		}

		void TransformComponent::setScale(const fmath::Vector3& scale) {
			this->m_isDirty = true;
			this->m_scaling = scale;
		}

		void TransformComponent::setRotation(const fmath::Quaternion q) {
			this->m_isDirty = true;
			this->m_rotation = q;
		}

		const fmath::Vector3& TransformComponent::getPosition() const {
			return this->m_position;
		}

		const fmath::Vector3& TransformComponent::getScale() const {
			return this->m_scaling;
		}

		const fmath::Quaternion& TransformComponent::getRotation() const {
			return this->m_rotation;
		}

		const fmath::Matrix4& TransformComponent::getWorldMatrix() const {
			return this->world_matrix;
		}
	}
}