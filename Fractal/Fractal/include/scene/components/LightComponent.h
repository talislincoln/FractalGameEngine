#ifndef _LIGHTCOMPONENT_H
#define _LIGHTCOMPONENT_H

#include <Fractal\include\scene\Component.h>
#include <FractalMath\Vector.h>

namespace fractal {
	namespace fscene {
		class LightComponent : public Component {
		public:
			LightComponent(const fmath::Vector3& colour);
			virtual ~LightComponent();

			virtual bool initialize();
			virtual void draw();
			virtual void update();
			virtual bool shutdown();

			inline void setColour(const fmath::Vector3& c) {
				m_colour = c;
			}

			inline const fmath::Vector3& getColour() const {
				return m_colour;
			}

		private:
			fmath::Vector3 m_colour;
		};
	}
}

#endif // !_LIGHTCOMPONENT_H
