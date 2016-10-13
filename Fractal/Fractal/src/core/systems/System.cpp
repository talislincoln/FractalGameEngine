#include "core\systems\System.h"

namespace fractal {
	namespace fcore {
		System::System(SystemType type)
			:m_systemType(type)
			, m_active(true)
		{
		}
		System::~System()
		{
		}

		void System::activate()
		{
			this->m_active = true;
		}
		void System::deactivate()
		{
			this->m_active = false;
		}

		bool System::getIsActive() const
		{
			return this->m_active;
		}

		SystemType System::getType() const
		{
			return this->m_systemType;
		}
	}
}