#include "utils\ShaderUtils\UniformVector4.h"

fractal::UniformVector4::UniformVector4(const char* name) : Uniform(name), m_used(false)
{
}

void fractal::UniformVector4::loadVector4(float x, float y, float z, float w)
{
	if (!m_used || x != m_currentX || y != m_currentY || z != m_currentZ) {
		m_currentX = x;
		m_currentY = y;
		m_currentZ = z;
		m_currentZ = w;
		m_used = true;
		glUniform4f(getLocation(), x, y, z, w);
	}
}

void fractal::UniformVector4::loadVector4(fmath::Vector4& v)
{
	loadVector4(v.x, v.y, v.z, v.w);
}


