#include "utils\ShaderUtils\UniformFloat.h"

using namespace fractal;
UniformFloat::UniformFloat(char* name) : Uniform(name) {

}

void fractal::UniformFloat::loadFloat(float f)
{
	if (!m_used || m_currentValue != f) {
		glUniform1f(getLocation(), f);
		m_used = true;
		m_currentValue = f;
	}
}
