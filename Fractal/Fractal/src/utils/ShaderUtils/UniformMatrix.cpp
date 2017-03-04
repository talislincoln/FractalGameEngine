#include "utils\ShaderUtils\UniformMatrix.h"

fractal::UniformMatrix::UniformMatrix(std::string& name) : Uniform(name)
{
}

void fractal::UniformMatrix::loadMatrix(fmath::Matrix4& matrix)
{
	m_matrix = matrix;
	glUniformMatrix4fv(getLocation(), 1 , false, m_matrix);
}
