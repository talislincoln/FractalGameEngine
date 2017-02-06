#include "core\systems\Timer.h"

namespace fractal {
	namespace fcore {
		Timer::Timer() :
			System(SystemType::TIMER_SYSTEM),
			m_worldTimer(nullptr)
		{
			//empty
		}

		Timer::~Timer() {
			//empty
		}

		bool Timer::initialize() {
			return true;
		}

		void Timer::update() {

		}

		bool Timer::shutdown() {
			return true;
		}
	}
}



