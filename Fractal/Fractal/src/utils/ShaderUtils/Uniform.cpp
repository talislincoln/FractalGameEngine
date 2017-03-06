#include "utils\ShaderUtils\Uniform.h"

fractal::Uniform::Uniform(const char* name) : m_name(name)
{
}

void fractal::Uniform::storeUniformLocation(int programID)
{
	m_location = glGetUniformLocation(programID, m_name);
	if (m_location == NOT_FOUND) {
		printf("No uniform variable called %s found!", m_name);
	}
}