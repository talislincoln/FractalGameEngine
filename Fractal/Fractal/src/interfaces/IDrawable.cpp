#include "interfaces\IDrawable.h"
namespace fractal {
	IDrawable::IDrawable()
		:m_canDraw(true)
	{
	}

	IDrawable::~IDrawable()
	{
	}

	void IDrawable::setCanDraw(bool canDraw)
	{
		this->m_canDraw = canDraw;
	}

	bool IDrawable::getCanDraw() const
	{
		return this->m_canDraw;
	}
}