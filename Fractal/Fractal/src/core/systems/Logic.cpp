#include "helpers\Singleton.h"
#include "core\systems\Logic.h"

#include "scene\SceneManager.h"

#include <assert.h>

namespace fractal {
	namespace fcore {
		Logic::Logic() :
			System(SystemType::LOGIC_SYSTEM),
			m_game(nullptr)
		{
			//empty
		}

		Logic::~Logic() {
			//empty
		}

		bool Logic::initialize() {
			//Game cannot be null!
			assert(this->m_game != nullptr);

			if (!m_game->initialize())
				return false;

			if (!fhelpers::Singleton<fscene::SceneManager>::getInstance().initialize())
				return false;

			return true;
		}

		void Logic::update() {
			fhelpers::Singleton<fscene::SceneManager>::getInstance().update();
		}

		void Logic::draw() const {
			if (fhelpers::Singleton<fscene::SceneManager>::getInstance().getCanDraw())
				fhelpers::Singleton<fscene::SceneManager>::getInstance().draw();
		}

		bool Logic::shutdown() {
			if (!fhelpers::Singleton<fscene::SceneManager>::getInstance().shutdown())
				return false;

			if (!m_game->shutdown())
				return false;

			return true;
		}

		void Logic::setGame(AbstractGame* game) {
			this->m_game = game;
		}
	}
}