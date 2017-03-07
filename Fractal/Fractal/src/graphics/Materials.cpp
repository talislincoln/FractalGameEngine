#include "graphics\Materials.h"
namespace fractal {
	namespace graphics {
	}
}

void fractal::fgraphics::Materials::bindMaterial()
{
}

void fractal::fgraphics::Materials::unbindMaterial()
{
}

void fractal::fgraphics::Materials::use()
{
	m_shader->use();
}

void fractal::fgraphics::Materials::unuse()
{

	m_shader->unuse();
}

void fractal::fgraphics::Materials::destroy()
{
	m_shader->destroy();
}
