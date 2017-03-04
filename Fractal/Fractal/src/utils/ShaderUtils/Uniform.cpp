#include "utils\ShaderUtils\Uniform.h"

fractal::Uniform::Uniform(std::string& name) : m_name(name)
{
}

void fractal::Uniform::storeUniformLocation(int programID)
{
	m_location = glGetUniformLocation(programID, m_name.c_str());
	if (m_location == NOT_FOUND) {
		printf("No uniform variable called %s found!", m_name);
	}
}