#include "scene\Component.h"

namespace fractal {
	namespace fscene {
		Component::Component(const std::string& name)
			: Object(name), m_parent(nullptr), m_orderId(INVALID_ORDER_ID)
		{
		}

		Component::~Component()
		{
		}

		const int Component::getOrderValue() const
		{
			return this->m_orderId;
		}
		void Component::setOrderValue(int value)
		{
			this->m_orderId = value;
		}

		void Component::setParent(GameObject* parent)
		{
			this->m_parent = parent;
		}
		GameObject* Component::getParent() const
		{
			return this->m_parent;
		}
	}
}