#ifndef _POLYGONSHAPE_H
#define _POLYGONSHAPE_H

#include "Shape.h"
#include <FractalMath\Point.h>
#include <vector>

namespace fractal {
	namespace fscene {
		class PolygonShape : public Shape {
		public:
			PolygonShape(fmath::Point3* points, int size);
			PolygonShape(const std::vector<fmath::Point3>& vecPoints);
			virtual ~PolygonShape();

			virtual void draw();
		private:
			std::vector<fmath::Point3> m_points;
		};
	}
}

#endif // !_POLYGONSHAPE_H

