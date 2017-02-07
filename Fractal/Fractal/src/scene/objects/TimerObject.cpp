#include "scene\objects\TimerObject.h"
#include <SDL\SDL.h>

namespace fractal {
	namespace fscene {
		TimerObject::TimerObject(const std::string& name) :
			Object(name),
			m_stopped(false),
			m_baseTime(0),
			m_pauseTime(0),
			m_stopTime(0),
			m_previousTime(0),
			m_currentTime(0),
			m_secondsPerCount(0.0),
			m_deltaTime(-1.0)
		{
			m_secondsPerCount = 1.0/static_cast<double>(SDL_GetPerformanceFrequency());
		}

		TimerObject::~TimerObject() {

		}

		bool TimerObject::initialize() {
			
			start();
			return true;
		}

		void TimerObject::update() {
			if (m_stopped) {
				m_deltaTime = 0.0;
			}

			Uint64 currTime = SDL_GetPerformanceCounter();
			m_currentTime = currTime;

			m_deltaTime = (m_currentTime - m_previousTime) * m_secondsPerCount;

			m_previousTime = m_currentTime;

			if (m_deltaTime < 0.0) {
				m_deltaTime = 0.0;
			}
		}

		bool TimerObject::shutdown() {
			stop();
			return true;
		}

		float TimerObject::getTotalTime() const {
			if (m_stopped) {
				return static_cast<float>((m_stopTime - m_baseTime) * m_secondsPerCount);
			}
			else {
				return static_cast<float>((m_currentTime - m_pauseTime) * m_secondsPerCount);
			}
		}

		void TimerObject::reset() {
			Uint64 currentTime = SDL_GetPerformanceCounter();

			m_baseTime = currentTime;
			m_previousTime = currentTime;
			m_stopTime = 0;

			m_stopped = false;
		}

		void TimerObject::start() {
			Uint64 startTime = SDL_GetPerformanceCounter();

			m_previousTime = startTime;

			if (m_stopped) {
				m_pauseTime += (startTime - m_stopTime);

				m_previousTime = startTime;

				m_stopTime = 0;
				m_stopped = false;
			}
		}

		void TimerObject::stop() {
			if (!m_stopped) {
				Uint64 newTicks = SDL_GetPerformanceCounter();

				m_stopTime = newTicks;
				m_stopped = true;
			}
		}
	}
}