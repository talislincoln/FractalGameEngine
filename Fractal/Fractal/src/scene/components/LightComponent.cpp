#include "scene\components\LightComponent.h"

namespace fractal {
	namespace fscene {
		LightComponent::LightComponent(const fmath::Vector3& colour) :
			Component("LightComponent"),
			m_colour(colour)
		{
			//empty
		}

		LightComponent::~LightComponent() {
			//empty
		}

		bool LightComponent::initialize() {
			return true;
		}

		void LightComponent::draw() {
			//empty maybe???
		}

		void LightComponent::update() {

		}

		bool LightComponent::shutdown() {
			return true;
		}
	}
}