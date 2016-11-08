#include "Component.h"


namespace fractal {

	Component::Component()
	{
	}


	Component::~Component()
	{
	}
	void Component::setParent(Object *p) {
		*this->parent = *p;
	}

}