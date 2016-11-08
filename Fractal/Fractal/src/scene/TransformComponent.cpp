#include "scene\TransformComponent.h"
#include "scene\GameObject.h"

namespace fractal {
	namespace fscene {
		TransformComponent::TransformComponent(const std::string& name) :
			Component(name == "" ? "TransformComponent" : name),
			m_isDirty(false),
			m_position(),
			m_scaling(),
			m_rotation(0.0f)
		{

		}

		TransformComponent::~TransformComponent() {

		}

		bool TransformComponent::initialize() {
			return true;
		}

		void TransformComponent::update() {
			if (!this->m_isDirty)
				return;

			/*Matrix2D mat_translation = Matrix2D::createTranslationMatrix(this->position);
			Matrix2D mat_scale = Matrix2D::createScalingMatrix(this->scaling);
			Matrix2D mat_rotation = Matrix2D::createRotationMatrix(this->rotation);

			this->world_matrix = mat_scale*mat_rotation*mat_translation;*/

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

		void TransformComponent::rotate(float rotation) {
			setRotation(getRotation() + rotation);

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

		void TransformComponent::setRotation(float angle) {
			this->m_isDirty = true;
			this->m_rotation = angle;
		}

		const fmath::Vector3& TransformComponent::getPosition() const {
			return this->m_position;
		}

		const fmath::Vector3& TransformComponent::getScale() const {
			return this->m_scaling;
		}

		float TransformComponent::getRotation() const {
			return this->m_rotation;
		}
	}
}