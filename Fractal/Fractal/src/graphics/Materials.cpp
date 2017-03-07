#include "graphics\Materials.h"
using namespace fractal;
using namespace fgraphics;
	void Materials::bindMaterial()
	{
	}

	void Materials::unbindMaterial()
	{
	}

	void Materials::use()
	{
		m_shader->use();
	}

	void Materials::unuse()
	{

		m_shader->unuse();
	}

	void Materials::destroy()
	{
		m_shader->destroy();
	}
