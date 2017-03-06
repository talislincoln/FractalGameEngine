#include "utils\ShaderUtils\UniformVector3.h"

fractal::UniformVector3::UniformVector3(char* name) : Uniform(name), m_used(false)
{
}

void fractal::UniformVector3::loadVector3(float x, float y, float z)
{
	if (!m_used || x != m_currentX || y != m_currentY || z != m_currentZ) {
		m_currentX = x;
		m_currentY = y;
		m_currentZ = z;
		m_used = true;
		glUniform3f(getLocation(), x, y , z);
	}
}

void fractal::UniformVector3::loadVector3(fmath::Vector3& v)
{
	loadVector3(v.x, v.y, v.z);
}


