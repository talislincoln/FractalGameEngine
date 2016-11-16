#include "scene\Shape.h"
#include "scene\ShapeComponent.h"

#include "defines\deletemacros.h"

namespace fractal {
	namespace fscene {
		ShapeComponent::ShapeComponent(Shape* shape) : m_shape(shape){
			//empty
		}

		ShapeComponent::~ShapeComponent() {
			
		}

		bool ShapeComponent::initialize() {
			return true;
		}

		void ShapeComponent::draw() {

		}

		void ShapeComponent::update() {

		}

		bool ShapeComponent::shutdown() {
			SafeDelete(m_shape);
			return true;
		}
	}
}