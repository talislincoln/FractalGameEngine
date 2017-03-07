#ifndef UNIFORM_VECTOR_2_H
#define UNIFORM_VECTOR_2_H
#include <Fractal\include\utils\ShaderUtils\Uniform.h>
#include <FractalMath\Math.h>
namespace fractal {

	class UniformVector2 : public Uniform {
	public:
		UniformVector2(const char* name);
		void loadVector2(float x, float y);
		void loadVector2(fmath::Vector2& v);
		void loadVector2(fmath::Vector3& v);


	private:
		float m_currentX;
		float m_currentY;
		bool m_used = false;
	};

}
#endif // !UNIFORM_VECTOR_2_H
