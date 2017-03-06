#include "utils\ShaderUtils\UniformMatrix.h"

fractal::UniformMatrix::UniformMatrix(const char* name) : Uniform(name)
{
}

void fractal::UniformMatrix::loadMatrix(const fmath::Matrix4& matrix)
{
	m_matrix = matrix;
	glUniformMatrix4fv(getLocation(), 1 , false, m_matrix);
}
