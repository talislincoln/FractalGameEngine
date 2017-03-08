#include "graphics\Material.h"
using namespace fractal;
using namespace fgraphics;

	void Material::use()
	{
		for (unsigned int i = 0; i < m_textures.size(); i++) {

			m_textures[i]->bindToUnit(i);
		}
		m_shader->use();
	}

	void Material::unuse()
	{
		m_shader->unuse();
	}

	void Material::destroy()
	{
		for (unsigned int i = 0; i < m_uniforms.size(); i++) {
			delete m_uniforms[i];
		}
		for (unsigned int i = 0; i < m_textures.size(); i++) {
			m_textures[i]->destroy();
		}
		m_shader->destroy();
	}

	void Material::loadCamera(const fmath::Matrix4& view,const fmath::Matrix4& projection, const fmath::Matrix4& model)
	{
		static_cast<UniformMatrix*>(m_uniforms[0])->loadMatrix(view);
		static_cast<UniformMatrix*>(m_uniforms[1])->loadMatrix(projection);
		static_cast<UniformMatrix*>(m_uniforms[2])->loadMatrix(model);
	}
