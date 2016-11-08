#pragma once
#include "Object.h"

namespace fractal {
	class Component : public Object
	{
	public:
		Component();
		virtual ~Component();

	protected:
		Object* parent;
		void setParent(Object *p);
	};

}