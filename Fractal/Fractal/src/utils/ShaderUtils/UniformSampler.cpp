#include "utils\ShaderUtils\UniformSampler.h"

fractal::UniformSampler::UniformSampler(std::string & name) : Uniform(name), m_used(false)
{
}

void fractal::UniformSampler::loadTextureUnit(int TextureID)
{
	if (!m_used || m_currentValue != TextureID) {
		glUniform1i(getLocation(), TextureID);
		m_used = true;
		m_currentValue = TextureID;
	}
}
