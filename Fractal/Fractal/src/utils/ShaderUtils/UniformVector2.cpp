#include "utils\ShaderUtils\UniformVector2.h"

fractal::UniformVector2::UniformVector2(const char* name) : Uniform(name), m_used(false)
{
}

void fractal::UniformVector2::loadVector2(float x, float y)
{
	if (!m_used || x != m_currentX || y != m_currentY) {
		m_currentX = x;
		m_currentY = y;
		m_used = true;
		glUniform2f(getLocation(), x, y);
	}
}

void fractal::UniformVector2::loadVector2(fmath::Vector2& v)
{
	loadVector2(v.x, v.y);
}

void fractal::UniformVector2::loadVector2(fmath::Vector3& v)
{
	loadVector2(v.x, v.y);
}

