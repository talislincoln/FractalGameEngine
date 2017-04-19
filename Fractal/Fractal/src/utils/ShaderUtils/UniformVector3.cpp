#include "utils\ShaderUtils\UniformVector3.h"

fractal::UniformVector3::UniformVector3(const char* name) : Uniform(name), m_used(false)
{
}

void fractal::UniformVector3::loadVector3(float x, float y, float z)
{
	loadVector3(fmath::Vector3(x, y, z));
}

void fractal::UniformVector3::loadVector3(const fmath::Vector3& v)
{
	if (!m_used || v.x != m_currentX || v.y != m_currentY || v.z != m_currentZ) {
		m_currentX = v.x;
		m_currentY = v.y;
		m_currentZ = v.z;
		m_used = true;
		glUniform3f(getLocation(), v.x, v.y, v.z);
	}
}


