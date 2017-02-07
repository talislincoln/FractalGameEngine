#include "core\systems\Timer.h"

#include <scene\objects\TimerObject.h>
#include <defines\deletemacros.h>

namespace fractal {
	namespace fcore {
		float Timer::deltaTime = 0.0f;

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
			m_worldTimer = new fscene::TimerObject("WorldTimer");

			if (!m_worldTimer->initialize()) {
				return false;
			}

			m_worldTimer->setInitialized();

			return true;
		}

		void Timer::update() {
			m_worldTimer->update();
			deltaTime = m_worldTimer->getDeltaTime();

			for (fscene::TimerObject* timer : m_timerObjects) {
				timer->update();
			}
		}

		bool Timer::shutdown() {
			SafeDelete(m_worldTimer);

			for (fscene::TimerObject* timer : m_timerObjects) {
				if (!timer->shutdown()) {
					return false;
				}

				SafeDelete(timer);
			}

			return true;
		}

		void Timer::addTimer(fscene::TimerObject* timerObejct) {

		}

		fscene::TimerObject* Timer::getTimer(const std::string& name) const {
			return NULL;
		}
	}
}



