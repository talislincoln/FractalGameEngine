#include "scene\SceneManager.h"
#include "scene\Scene.h"
#include "defines\deletemacros.h"

#ifndef _ALGORITHM_
#include <algorithm>
#endif

#include <cassert>

namespace fractal {
	namespace fscene {
		SceneManager::SceneManager()
			:m_activeScene(nullptr)
		{
		}

		SceneManager::~SceneManager()
		{
		}

		bool SceneManager::initialize()
		{
			//define wheather or not we need those managers
			//setupManager<Renderer>();
			//setupManager<CameraManager>();

			if (!this->m_activeScene->isInitialized())
			{
				//this->m_activeScene->setRenderer(&Singleton<Renderer>::getInstance());
				//this->m_activeScene->setCameraManager(&Singleton<CameraManager>::getInstance());

				if (!this->m_activeScene->initialize())
					return false;
				this->m_activeScene->setInitialized();
			}

			return true;
		}

		void SceneManager::update()
		{
			//Initialize the scene before trying to update it.
			assert(this->m_activeScene->isInitialized());

			if (this->m_activeScene->isActive())
				this->m_activeScene->update();
		}

		void SceneManager::draw()
		{

			if (!this->m_activeScene->isInitialized()) {
				this->m_activeScene->initialize();
			}
			//Initialize the scene before trying to draw it.
			assert(this->m_activeScene->isInitialized());

			if (this->m_activeScene->getCanDraw() && this->m_activeScene->isActive())
				this->m_activeScene->draw();
		}

		bool SceneManager::shutdown()
		{
			for (Scene* scene : this->m_scenes)
			{
				if (!scene->isInitialized())
				{
					SafeDelete(scene);
					continue;
				}

				if (!scene->shutdown())
					return false;

				SafeDelete(scene);
			}

			//destroyManager<Renderer>();
			//destroyManager<CameraManager>();

			return true;
		}

		void SceneManager::addScene(Scene* scene)
		{
			std::vector<Scene*>::iterator it = std::find(m_scenes.begin(), m_scenes.end(), scene);
			if (it == m_scenes.end())
				m_scenes.push_back(scene);
		}

		void SceneManager::setActiveScene(const std::string& name)
		{
			std::vector<Scene*>::iterator it = std::find_if(m_scenes.begin(), m_scenes.end(),
				[name](Scene* scene) -> bool
			{
				return scene->getName() == name;
			});

			//Scene with given name was not found.
			assert(it != m_scenes.end());

			if (this->m_activeScene)
			{
				this->m_activeScene->deactive();
				this->m_activeScene->destroy();
			}

			this->m_activeScene = (*it);
			this->m_activeScene->activate();


		}

		Scene* SceneManager::getActiveScene() const
		{
			return this->m_activeScene;
		}
	}
}