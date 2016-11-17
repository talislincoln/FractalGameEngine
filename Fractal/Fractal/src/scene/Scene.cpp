#include "scene\Scene.h"

#include "scene\GameObject.h"
#include "helpers\Singleton.h"
#include "core\systems\Input.h"
#include "core\systems\manager\SystemManager.h"

namespace fractal {
	namespace fscene {
		Scene::Scene(const std::string& name)
			:Object(name)
			//, renderer(nullptr)
			//, camera_manager(nullptr)
		{
		}

		Scene::~Scene()
		{
		}

		bool Scene::initialize()
		{
			fcore::Input* input = dynamic_cast<fcore::Input*>(fhelpers::Singleton<fcore::SystemManager>::getInstance().getSystem(SystemType::INPUT_SYSTEM));
			this->setupInput(input);

			for (GameObject* obj : this->m_objects)
			{
				if (obj->isInitialized())
					continue;

				if (!obj->initialize())
					return false;
			}

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
		void Scene::draw()
		{
			for (GameObject* obj : this->m_objects)
			{
				//checking if the objects inherits from the IDrawable class
				//if not, then continue to the next object; draw it otherwise
				IDrawable* drawable_obj = dynamic_cast<IDrawable*>(obj);
				if (drawable_obj == nullptr)
					continue;

				if (drawable_obj->getCanDraw())
					drawable_obj->draw();
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
	}
}