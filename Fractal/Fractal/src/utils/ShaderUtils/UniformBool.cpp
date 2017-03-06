#include "utils\ShaderUtils\UniformBool.h"

using namespace fractal;
UniformBool::UniformBool(char* name) : Uniform(name) {

}

void fractal::UniformBool::loadBool(bool boolean)
{
	if (!m_used || m_currentBool != boolean) {
		glUniform1f(getLocation(), boolean ? 1.0f : 0.0f);
		m_used = true;
		m_currentBool = boolean;
	}
}
