#ifndef _VERTEX_H
#define _VERTEX_H
#include <FractalMath\Point.h>

namespace fractal {
	namespace fgraphics {
		struct UV {
			float u;
			float v;
		};

		struct Vertex {
			fmath::Point3 position;

			Vertex(fmath::Point3 p) : position(p) {

			}
		};
	}
}

#endif // !_VERTEX_H
