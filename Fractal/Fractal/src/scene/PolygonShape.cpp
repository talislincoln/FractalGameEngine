#include "scene\PolygonShape.h"

namespace fractal {
	namespace fscene {
		PolygonShape::PolygonShape(fmath::Point3* points, int size) :
			PolygonShape(std::vector<fmath::Point3>(points, points + size))
		{
			//empty
		}

		PolygonShape::PolygonShape(const std::vector<fmath::Point3>& vecPoints) :
			m_points(vecPoints)
		{

		}

		PolygonShape::~PolygonShape() {

		}
			 
		void PolygonShape::draw() {

		}
	}
}