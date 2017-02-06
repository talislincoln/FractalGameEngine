#include "scene\objects\TimerObject.h"
#include <SDL\SDL.h>

namespace fractal {
	namespace fscene {
		TimerObject::TimerObject(const std::string& name) :
			Object(name),
			m_currentTime(0),
			m_previousTime(0),
			m_deltaTime(-1),
			m_stopped(false)
		{
			m_previousTime = SDL_GetTicks();
		}

		TimerObject::~TimerObject() {

		}

		bool TimerObject::initialize() {
			
			start();
			return true;
		}

		void TimerObject::update() {
			if (m_stopped) {
				m_deltaTime = 0.0f;
			}

			// Calculate the frameTime in milliseconds
			float newTicks = SDL_GetTicks();
			float frameTime = newTicks - m_previousTime;
			m_previousTime = newTicks;

			m_deltaTime = (frameTime / DESIRED_FRAMETIME);

			if (m_deltaTime < 0.0f) {
				m_deltaTime = 0.0f;
			}
		}

		bool TimerObject::shutdown() {
			stop();
			return true;
		}

		float TimerObject::getTotalTime() const {
			if (m_stopped) {
				return (m_stopTime - m_baseTime) / DESIRED_FRAMETIME;
			}
			else {
				return (m_currentTime - m_pauseTime) / DESIRED_FRAMETIME;
			}
		}

		void TimerObject::reset() {
			float currentTime = SDL_GetTicks();

			m_baseTime = currentTime;
			m_previousTime = currentTime;
			m_stopTime = 0.0f;

			m_stopped = false;
		}

		void TimerObject::start() {
			float startTime = SDL_GetTicks();

			m_previousTime = startTime;

			if (m_stopped) {
				m_pauseTime += (startTime - m_stopTime);

				m_previousTime = startTime;

				m_stopTime = 0.0f;
				m_stopped = false;
			}
		}

		void TimerObject::stop() {
			if (!m_stopped) {
				float newTicks = SDL_GetTicks();

				m_stopTime = newTicks;
				m_stopped = true;
			}
		}
	}
}