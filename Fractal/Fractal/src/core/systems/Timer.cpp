#include "core\systems\Timer.h"

#include <scene\objects\TimerObject.h>
#include <defines\deletemacros.h>

namespace fractal {
	namespace fcore {
		float Timer::deltaTime = 0.0f;

		Timer::Timer() :
			System(SystemType::TIMER_SYSTEM),
			m_worldTimer(nullptr),
			m_maxFPS(60.0f),
			m_fps(60.0f)
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

		bool Timer::fixedUpdate() {
			return true;
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

		void Timer::startFPS() {
			m_startTicks = SDL_GetTicks();
		}

		float Timer::endFPS() {
			static const int NUM_SAMPLES = 10;
			static float frameTimes[NUM_SAMPLES];
			static int currentFrame = 0;
			static Uint32 previousTicks = SDL_GetTicks();

			Uint32 currentTicks;
			currentTicks = SDL_GetTicks();

			m_frameTime = currentTicks - previousTicks;
			frameTimes[currentFrame % NUM_SAMPLES] = m_frameTime;
			previousTicks = currentTicks;

			int count;
			currentFrame++;

			if (currentFrame < NUM_SAMPLES) {
				count = currentFrame;
			}
			else {
				count = NUM_SAMPLES;
			}

			float frameTimeAverage = 0;
			for (int i = 0; i < count; i++) {
				frameTimeAverage += frameTimes[i];
			}
			frameTimeAverage /= count;

			if (frameTimeAverage > 0) {
				m_fps = 1000.0f / frameTimeAverage;
			}
			else {
				m_fps = 60.0f;
			}

			float frameTicks = SDL_GetTicks() - m_startTicks;
			//limiting time measuring ^
			if (1000.0f / m_maxFPS > frameTicks) {
				SDL_Delay(1000.0f / m_maxFPS - frameTicks);
			}

			return m_fps;
		}

		void Timer::addTimer(fscene::TimerObject* timerObejct) {

		}

		fscene::TimerObject* Timer::getTimer(const std::string& name) const {
			return NULL;
		}
	}
}



