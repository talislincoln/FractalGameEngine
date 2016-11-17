#include "core\systems\System.h"

namespace fractal {
	namespace fcore {
		System::System(SystemType type)
			:m_systemType(type)
			, m_isActive(true)
		{
		}

		System::~System()
		{
		}

		void System::activate()
		{
			this->m_isActive = true;
		}
		void System::deactivate()
		{
			this->m_isActive = false;
		}

		bool System::getIsActive() const
		{
			return this->m_isActive;
		}

		SystemType System::getType() const
		{
			return this->m_systemType;
		}
	}
}