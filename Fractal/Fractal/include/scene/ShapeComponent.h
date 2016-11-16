#ifndef _SHAPECOMPONENT_H
#define _SHAPECOMPONENT_H

#include "scene\Component.h"
#include "defines\Colour.h"
#include "interfaces\IDrawable.h"

namespace fractal {
	namespace fscene {
		class Shape;
		class ShapeComponent : public Component, public IDrawable {
		public:
			ShapeComponent(Shape* shape);
			virtual ~ShapeComponent();

			virtual bool initialize();
			virtual void draw();
			virtual void update();
			virtual bool shutdown();

			inline void setColor(const Colour& c) {
				m_shape->setColor(c);
			}

			inline const Colour& getColor() const {
				return m_shape->getColor();
			}

		private:
			Shape* m_shape;
		};
	}
}

#endif // !_SHAPECOMPONENT_H
