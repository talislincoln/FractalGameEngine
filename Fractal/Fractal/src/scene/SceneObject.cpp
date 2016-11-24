#include "scene\SceneObject.h"

#include "scene\components\TransformComponent.h"

namespace fractal {
	namespace fscene {
		SceneObject::SceneObject(const std::string& name) :
			GameObject("name"),
			m_transform(new TransformComponent())
		{
			//empty
		}

		SceneObject::~SceneObject() {
			//empty
		}

		bool SceneObject::initialize() {
			addComponent(this->m_transform);
			return GameObject::initialize();
		}

		void SceneObject::update() {
			return GameObject::update();
		}

		void SceneObject::draw() {
			/*Matrix2D world_matrix = getTransform()->getWorldMatrix();
			Matrix2D view_matrix = getScene()->getCameraManager()->getActiveCamera()->getCamera()->getViewMatrix();

			getScene()->getRenderer()->setTransformMatrix(world_matrix * view_matrix);

			for (Component* obj : getComponents())
			{
				IDrawable* drawable_obj = dynamic_cast<IDrawable*>(obj);
				if (drawable_obj == nullptr)
					continue;

				if (drawable_obj->getCanDraw())
					drawable_obj->draw();
			}
			for (GameObject* obj : getChilderen())
			{
				IDrawable* drawable_obj = dynamic_cast<IDrawable*>(obj);
				if (drawable_obj == nullptr)
					continue;

				if (drawable_obj->getCanDraw())
					drawable_obj->draw();
			}

			getScene()->getRenderer()->setTransformMatrix(Matrix2D::createIdentityMatrix());*/

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

		bool SceneObject::shutdown() {
			return GameObject::shutdown();
		}

		TransformComponent* SceneObject::getTransform() const {
			return m_transform;
		}
	}
}