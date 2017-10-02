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
	//m_shader->destroy();
	m_shader = nullptr;
}

void fractal::fgraphics::Material::loadCamera(const fmath::Matrix4 & view, const fmath::Matrix4 & projection, const fmath::Matrix4 & model)
{
	static_cast<UniformMatrix*>(m_uniforms[0])->loadMatrix(view);
	static_cast<UniformMatrix*>(m_uniforms[1])->loadMatrix(projection);
	static_cast<UniformMatrix*>(m_uniforms[2])->loadMatrix(model);
}

void fractal::fgraphics::Material::loadProjectionMatrix(const fmath::Matrix4 & projection)
{
	static_cast<UniformMatrix*>(m_uniforms[0])->loadMatrix(projection);
}

void fractal::fgraphics::Material::loadViewMatrix(const fmath::Matrix4 & view)
{
	static_cast<UniformMatrix*>(m_uniforms[1])->loadMatrix(view);
}

void fractal::fgraphics::Material::load2DMatrix(const fmath::Vector2 & t, float rolate, const fmath::Vector2 & scale, int index)
{
	fmath::Matrix4 m = fmath::Matrix4::create2Dmatrix(t, rolate, scale);
	static_cast<UniformMatrix*>(m_uniforms[index])->loadMatrix(m);
}

void fractal::fgraphics::Material::loadShineVariables(float damper, float reflectivity, int damperIndex, int reflectivityIndex) {
	static_cast<UniformFloat*>(m_uniforms[damperIndex])->loadFloat(damper);
	static_cast<UniformFloat*>(m_uniforms[reflectivityIndex])->loadFloat(reflectivity);
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
//;w; loading light stuff
void fractal::fgraphics::Material::loadProperties(const fmath::Vector3& viewPos) {
	static_cast<UniformVector3*>(m_uniforms[3])->loadVector3(viewPos);
}
void fractal::fgraphics::Material::loadMaterial(const float materialDiffuse, const float materialSpecular, const float materialLuster) {
	static_cast<UniformFloat*>(m_uniforms[4])->loadFloat(materialDiffuse);
	static_cast<UniformFloat*>(m_uniforms[5])->loadFloat(materialSpecular);
	static_cast<UniformFloat*>(m_uniforms[6])->loadFloat(materialLuster);
}
void fractal::fgraphics::Material::loadDirectional(const fmath::Vector3& direction, const fmath::Vector3& ambient, const fmath::Vector3& diffuse, const fmath::Vector3& specular) {
	static_cast<UniformVector3*>(m_uniforms[7])->loadVector3(direction);
	static_cast<UniformVector3*>(m_uniforms[8])->loadVector3(ambient);
	static_cast<UniformVector3*>(m_uniforms[9])->loadVector3(diffuse);
	static_cast<UniformVector3*>(m_uniforms[10])->loadVector3(specular);
}
void fractal::fgraphics::Material::loadPoint(const fmath::Vector3& position, const fmath::Vector3& ambient, const fmath::Vector3& diffuse, const fmath::Vector3& specular,
	const float& constant, const float& linear, const float& quadratic) {
	static_cast<UniformVector3*>(m_uniforms[11])->loadVector3(position);
	static_cast<UniformVector3*>(m_uniforms[12])->loadVector3(ambient);
	static_cast<UniformVector3*>(m_uniforms[13])->loadVector3(diffuse);
	static_cast<UniformVector3*>(m_uniforms[14])->loadVector3(specular);
	static_cast<UniformFloat*>(m_uniforms[15])->loadFloat(constant);
	static_cast<UniformFloat*>(m_uniforms[16])->loadFloat(linear);
	static_cast<UniformFloat*>(m_uniforms[17])->loadFloat(quadratic);
}
void fractal::fgraphics::Material::loadSpot(const fmath::Vector3& position, const fmath::Vector3& direction, const fmath::Vector3& ambient, const fmath::Vector3& diffuse, const fmath::Vector3& specular,
	const float& constant, const float& linear, const float& quadratic, const float& cutoff, const float& outerCutoff) {
	static_cast<UniformVector3*>(m_uniforms[18])->loadVector3(position);
	static_cast<UniformVector3*>(m_uniforms[19])->loadVector3(direction);
	static_cast<UniformVector3*>(m_uniforms[20])->loadVector3(ambient);
	static_cast<UniformVector3*>(m_uniforms[21])->loadVector3(diffuse);
	static_cast<UniformVector3*>(m_uniforms[22])->loadVector3(specular);
	static_cast<UniformFloat*>(m_uniforms[23])->loadFloat(constant);
	static_cast<UniformFloat*>(m_uniforms[24])->loadFloat(linear);
	static_cast<UniformFloat*>(m_uniforms[25])->loadFloat(quadratic);
	static_cast<UniformFloat*>(m_uniforms[26])->loadFloat(cutoff);
	static_cast<UniformFloat*>(m_uniforms[27])->loadFloat(outerCutoff);
}