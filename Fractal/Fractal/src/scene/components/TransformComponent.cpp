#include "scene\components\TransformComponent.h"
#include "scene\GameObject.h"

namespace fractal {
	namespace fscene {
		TransformComponent::TransformComponent(const std::string& name) :
			Component(name == "" ? "TransformComponent" : name),
			m_isDirty(false),
			m_position(),
			m_scaling(1),
			m_rotation(),
			m_physicsChanges(false)
		{
			m_worldMatrix.loadIdentity();
		}

		TransformComponent::~TransformComponent() {
			//empty
		}

		bool TransformComponent::initialize() {
			return true;
		}

		void TransformComponent::update() {
			if (!this->m_isDirty)
				return;

			this->m_worldMatrix = fmath::Matrix4::scale(this->m_scaling) *
									(this->m_rotation.toMatrix()) *  
									fmath::Matrix4::translate(this->m_position);

			this->m_isDirty = false;
		}

		bool TransformComponent::shutdown() {
			return true;
		}

		void TransformComponent::setRotation(const fmath::Quaternion& q)
		{
			this->m_isDirty = true;
			this->m_physicsChanges = true;
			this->m_rotation = q;
			/*for (GameObject* obj : getParent()->getChildren())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->setRotation(q);
			}*/
		}
		void TransformComponent::setScale(const fmath::Vector3& scale)
		{
			this->m_isDirty = true;
			this->m_physicsChanges = true;
			this->m_scaling = scale;
			/*for (GameObject* obj : getParent()->getChildren())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->setScale(scale);
			}*/
		}
		void TransformComponent::setPosition(float x, float y, float z) {
			setPosition(fmath::Vector3(x,y,z));
		}
		void TransformComponent::setPosition(const fmath::Vector3& position)
		{
			this->m_isDirty = true;
			this->m_physicsChanges = true;
			this->m_position = position;
			//setPosition(getPosition() + translation);
/*
			for (GameObject* obj : getParent()->getChildren())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->setPosition(position);
			}*/
		}
		void TransformComponent::translate(const fmath::Vector3& translation) {
			this->m_isDirty = true;
			this->m_physicsChanges = true;
			m_position += translation;
			//setPosition(getPosition() + translation);

			for (GameObject* obj : getParent()->getChildren())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->translate(translation);
			}
		}

		void TransformComponent::scale(const fmath::Vector3& scale) {
			setScale(getScale() * scale);

			for (GameObject* obj : getParent()->getChildren())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->scale(scale);
			}
		}

		void TransformComponent::rotate(const fmath::Quaternion& rotation) {
			setRotation(getRotation() * rotation);

			for (GameObject* obj : getParent()->getChildren())
			{
				TransformComponent* transform = obj->getComponent<TransformComponent>();
				if (!transform)
					continue;

				transform->rotate(rotation);
			}
		}

	}
}