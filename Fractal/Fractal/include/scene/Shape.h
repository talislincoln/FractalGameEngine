#ifndef _SHAPE_H
#define _SHAPE_H

#include "defines\Colour.h"

namespace fractal {
	namespace fscene {
		
		class Shape {
		public:
			Shape();
			virtual ~Shape();

			virtual void draw() = 0;

			inline void setColor(const Colour& c) {
				m_colour = c;
			}
			const Colour& getColor() const {
				return this->m_colour;
			}
		private:
			Colour m_colour;
		};
	}
}

#endif // !_SHAPE_H
