#include "scene\GameObject.h"
#include "scene\Component.h"
#include "defines\deletemacros.h"
#include "scene\Scene.h"

namespace fractal {
	namespace fscene {
		GameObject::GameObject(const std::string& name)
			: Object(name), m_currentScene(nullptr), m_parent(nullptr),
			m_transformComponent(new TransformComponent())
		{
		}

		GameObject::~GameObject()
		{
		}

		bool GameObject::initialize()
		{
			//every game object has a Transform component by default
			addComponent(m_transformComponent);

			for (Component* component : this->m_components)
			{
				if (component->isInitialized())
					continue;

				if (!component->initialize())
					return false;
			}

			for (GameObject* child : this->m_children)
			{
				if (child->isInitialized())
					continue;

				if (!child->initialize())
					return false;
			}

			return true;
		}

		void GameObject::update()
		{
			for (Component* component : this->m_components)
			{
				if (component->isActive())
					component->update();
			}

			for (GameObject* child : this->m_children)
			{
				if (child->isActive())
					child->update();
			}
		}

		void GameObject::draw() const {
			for (Component* obj : getComponents())
			{
				IDrawable* drawable_obj = dynamic_cast<IDrawable*>(obj);
				if (drawable_obj == nullptr)
					continue;

				if (drawable_obj->getCanDraw())
					drawable_obj->draw();
			}

			for (GameObject* obj : getChildren())
			{
				IDrawable* drawable_obj = dynamic_cast<IDrawable*>(obj);
				if (drawable_obj == nullptr)
					continue;

				if (drawable_obj->getCanDraw())
					drawable_obj->draw();
			}
		}

		void GameObject::fixedUpdate()
		{
			// TODO: implement this
		}

		bool GameObject::shutdown()
		{
			for (Component* component : this->m_components)
			{
				if (!component->shutdown())
					return false;
				SafeDelete(component);
			}
			this->m_components.clear();
			for (GameObject* child : this->m_children)
			{
				if (!child->shutdown())
					return false;
				SafeDelete(child);
			}
			this->m_children.clear();
			return true;
		}

		void GameObject::setScene(Scene* scene)
		{
			this->m_currentScene = scene;
		}

		Scene* GameObject::getScene() const
		{
			return this->m_currentScene;
		}

		const GameObject* GameObject::getRootParent() const {
			if (getParent() == nullptr)
				return this;
			else 
				return getParent()->getRootParent();
		}
		void GameObject::setParent(GameObject* parent)
		{
			m_depth = parent->getDepth() + 1;
			this->m_parent = parent;
		}

		GameObject* GameObject::getParent() const
		{
			return this->m_parent;
		}

		std::vector<GameObject*> GameObject::getChildren() const
		{
			return this->m_children;
		}

		std::vector<Component*> GameObject::getComponents() const
		{
			return this->m_components;
		}

		TransformComponent* GameObject::getTransform() const {
			return m_transformComponent;
		}

		void GameObject::addComponent(Component* component)
		{
			std::vector<Component*>::iterator it = std::find(this->m_components.begin(), this->m_components.end(), component);
			if (it == this->m_components.end())
			{
				this->m_components.push_back(component);
				component->setParent(this);

				//init component whenever you it gets added
				//need to check for erros here!!!
				if (!component->isInitialized())
					component->initialize();

				if (component->getOrderValue() == Component::INVALID_ORDER_ID)
					component->setOrderValue(this->m_components.size());
			}
		}

		void GameObject::removeComponent(Component* component)
		{
			std::vector<Component*>::iterator it = std::find(this->m_components.begin(), this->m_components.end(), component);
			if (it != this->m_components.end())
			{
				this->m_components.erase(it);
				SafeDelete((*it));
			}
		}

		void GameObject::addChild(GameObject* child)
		{
			std::vector<GameObject*>::iterator it = std::find(this->m_children.begin(), this->m_children.end(), child);
			if (it == this->m_children.end())
			{
				this->m_children.push_back(child);
				child->setParent(this);
				child->setScene(getScene());
			}
		}
		unsigned int GameObject::getDepth() const
		{
			return m_depth;
		}
		void GameObject::removeChild(GameObject* child)
		{
			std::vector<GameObject*>::iterator it = std::find(this->m_children.begin(), this->m_children.end(), child);
			if (it != this->m_children.end())
			{
				//child->destroy();  when removing child. should destroy.. somehow
				this->m_children.erase(it);
				SafeDelete((*it));
			}
		}
	}
}