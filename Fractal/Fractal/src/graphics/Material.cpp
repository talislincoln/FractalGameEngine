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
		m_uniforms.clear();
		for (unsigned int i = 0; i < m_textures.size(); i++) {
			m_textures[i]->destroy();
		}
		m_textures.clear();
		m_shader->destroy();
		m_shader = nullptr;
	}

	void fractal::fgraphics::Material::loadCamera(const fmath::Matrix4 & view, const fmath::Matrix4 & projection, const fmath::Matrix4 & model)
	{
		static_cast<UniformMatrix*>(m_uniforms[0])->loadMatrix(view);
		static_cast<UniformMatrix*>(m_uniforms[1])->loadMatrix(projection);
		static_cast<UniformMatrix*>(m_uniforms[2])->loadMatrix(model);
	}

	void fractal::fgraphics::Material::load2DMatrix(const fmath::Vector2 & t, float rolate, const fmath::Vector2 & scale, int index)
	{
		fmath::Matrix4 m = fmath::Matrix4::create2Dmatrix(t, rolate, scale);
		static_cast<UniformMatrix*>(m_uniforms[index])->loadMatrix(m);
	}
	void Material::loadNewTexture(Texture * newTexture, const unsigned int location)
	{
		if (location < m_textures.size()) {
			std::vector<Texture*>::iterator it;
			it = m_textures.begin() + location;
			it = m_textures.erase(it);
			it = m_textures.insert(it, newTexture);
			this->loadTexture();
		}
	}

	void fractal::fgraphics::Material::loadTransform(const fmath::Matrix4& TransformMatrix, unsigned int location)
	{

		static_cast<UniformMatrix*>(m_uniforms[location])->loadMatrix(TransformMatrix);
	}

