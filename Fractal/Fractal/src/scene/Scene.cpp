#include "scene\Scene.h"

#include "scene\GameObject.h"
#include "helpers\Singleton.h"
#include "core\systems\Input.h"
#include "core\systems\manager\SystemManager.h"

#include <core\systems\Engine.h>

namespace fractal {
	namespace fscene {
		Scene::Scene(const std::string& name) :
			Object(name)
			//, m_cameraManager(nullptr)
			//, renderer(nullptr)
		{
		}

		Scene::~Scene()
		{
		}

		bool Scene::initialize()
		{
			input = INPUT_SYSTEM;
			this->setupInput(input);

			for (GameObject* obj : this->m_objects)
			{
				if (obj->isInitialized())
					continue;

				if (!obj->initialize())
					return false;
			}
			this->setInitialized();
			return true;
		}

		void Scene::update()
		{
			for (GameObject* obj : this->m_objects)
			{
				if (obj->isActive())
					obj->update();
			}
		}

		void Scene::draw() const
		{
			for (GameObject* obj : this->m_objects)
			{

				if (obj->getCanDraw())
					obj->draw();
			}
		}

		bool Scene::shutdown()
		{
			for (GameObject* obj : this->m_objects)
			{
				if (!obj->shutdown())
					return false;
				SafeDelete(obj);
			}
			this->m_objects.clear();

			return true;
		}

		void Scene::setupInput(fcore::Input* input)
		{

		}

		void Scene::activate()
		{
			Object::activate();
		}
		void Scene::deactive()
		{
			Object::deactive();
		}

		void Scene::destroy()
		{
			Object::destroy();
		}

		void Scene::addGameObject(GameObject* object)
		{
			std::vector<GameObject*>::iterator it = std::find(this->m_objects.begin(), this->m_objects.end(), object);
			if (it == this->m_objects.end())
			{
				this->m_objects.push_back(object);
				object->setScene(this);
			}
		}

		void Scene::removeGameObject(GameObject* object)
		{
			std::vector<GameObject*>::iterator it = std::find(this->m_objects.begin(), this->m_objects.end(), object);
			if (it != this->m_objects.end())
			{
				this->m_objects.erase(it);
				SafeDelete((*it));
			}
		}

		/*void Scene::setCameraManager(fcore::CameraManager* manager) {
			m_cameraManager = manager;
		}

		fcore::CameraManager* Scene::getCameraManager() const {
			return m_cameraManager;
		}*/
	}
}