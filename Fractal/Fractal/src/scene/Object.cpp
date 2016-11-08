#include "scene\Object.h"

namespace fractal {
	namespace fscene {
		Object::Object(const std::string& name)
			: m_isActive(true), m_isInitialized(false),
			m_isDestroyed(false)
		{
			this->name = name == "" ? generateName<Object>("Object_") : name;
		}

		Object::~Object()
		{
		}

		void Object::setInitialized()
		{
			this->m_isInitialized = true;
		}

		const bool Object::isInitialized() const
		{
			return this->m_isInitialized;
		}

		void Object::activate()
		{
			this->m_isActive = true;
		}

		void Object::deactive()
		{
			this->m_isActive = false;
		}

		const bool Object::isActive() const
		{
			return this->m_isActive;
		}

		void Object::destroy()
		{
			this->m_isDestroyed = true;

			this->m_isInitialized = false;
		}
		bool Object::isDestroyed() const
		{
			return this->m_isDestroyed;
		}

		void Object::setName(const std::string& name)
		{
			this->name = name;
		}
		const std::string& Object::getName() const
		{
			return this->name;
		}
	}
}