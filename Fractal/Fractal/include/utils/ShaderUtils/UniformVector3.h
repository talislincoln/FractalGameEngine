#ifndef UNIFORM_VECTOR_3_H
#define UNIFORM_VECTOR_3_H

#include <Fractal\include\utils\ShaderUtils\Uniform.h>

#include <FractalMath\Math.h>

namespace fractal {

	class UniformVector3 : public Uniform {
	public:
		UniformVector3(const char* name);
		void loadVector3(float x, float y, float z);
		void loadVector3(const fmath::Vector3& v);


	private:
		float m_currentX;
		float m_currentY;
		float m_currentZ;
		bool m_used = false;

	};

}
#endif // !UNIFORM_VECTOR_3_H
