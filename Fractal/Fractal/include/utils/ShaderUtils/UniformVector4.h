#ifndef UNIFORM_VECTOR_4_H
#define UNIFORM_VECTOR_4_H

#include <Fractal\include\utils\ShaderUtils\Uniform.h>

#include <FractalMath\Math.h>

namespace fractal {

	class UniformVector4 : public Uniform {
	public:
		UniformVector4(std::string& name);
		void loadVector4(float x, float y, float z, float w);
		void loadVector4(fmath::Vector4& v);


	private:
		float m_currentX;
		float m_currentY;
		float m_currentZ;
		float m_currentW;
		bool m_used = false;

	};

}
#endif // !UNIFORM_VECTOR_4_H
#pragma once
