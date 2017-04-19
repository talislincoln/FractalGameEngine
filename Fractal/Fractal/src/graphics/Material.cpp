#include "graphics\Material.h"
#include "scene\components\LightComponent.h"

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

	void fractal::fgraphics::Material::loadLight(const fmath::Vector3& lightPos, const fmath::Vector3& lightColour)
	{
		static_cast<UniformVector3*>(m_uniforms[4])->loadVector3(lightPos);
		static_cast<UniformVector3*>(m_uniforms[3])->loadVector3(lightColour);
	}
	void fractal::fgraphics::Material::loadTest(const fmath::Vector3& lightAmbient, const fmath::Vector3& lightDiffuse, const fmath::Vector3& lightSpecular,
		const float lightConstant, const float lightLinear, const float lightQuadratic, const float materialDiffuse, const float materialSpecular, const float materialLuster) {
		static_cast<UniformVector3*>(m_uniforms[7])->loadVector3(lightAmbient);
		static_cast<UniformVector3*>(m_uniforms[8])->loadVector3(lightDiffuse);
		static_cast<UniformVector3*>(m_uniforms[9])->loadVector3(lightSpecular);
		static_cast<UniformFloat*>(m_uniforms[10])->loadFloat (lightConstant);
		static_cast<UniformFloat*>(m_uniforms[11])->loadFloat(lightLinear);
		static_cast<UniformFloat*>(m_uniforms[12])->loadFloat(lightQuadratic);
		static_cast<UniformFloat*>(m_uniforms[6])->loadFloat(materialLuster);
	}
	void fractal::fgraphics::Material::loadTest2(const fmath::Vector3& lightPos, const fmath::Vector3& ViewPos) {
		static_cast<UniformVector3*>(m_uniforms[13])->loadVector3(lightPos);
		static_cast<UniformVector3*>(m_uniforms[3])->loadVector3(ViewPos);
	}
