#ifndef _VERTEX_H
#define _VERTEX_H
#include <FractalMath\Vector.h>
#include <string>

namespace fractal {
	namespace fgraphics {
		struct Texture {
			unsigned int id;
			std::string type;
		};

		struct Vertex {
			fmath::Point3 position;

			Vertex(fmath::Point3 p) : position(p) {
			}
		};
	}
}

#endif // !_VERTEX_H