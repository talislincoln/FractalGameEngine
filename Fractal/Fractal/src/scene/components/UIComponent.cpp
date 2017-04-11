#include "scene\components\UIComponent.h"

#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"
#include "core\systems\manager\SystemManager.h"
#include <FractalMath\Matrix.h>
#include "scene\GameObject.h"
#include <assert.h>
#include "core\systems\manager\UIManager.h"
namespace fractal {
	namespace fHUD {
		using namespace fmath;
		UIComponent::UIComponent(fgraphics::Material* m) :
			Component("UIComponent"), m_isDirty(true), m_UIParent(nullptr), 
			m_material(m), m_offset(fmath::Vector2(0.0f, 0.0f)), m_rolation(0.0f), m_scale(Vector2(0.8f)), m_vao(new fgraphics::Vao())
		{
			//empty
		}

		UIComponent::~UIComponent() {
			//empty
		}

		bool UIComponent::initialize() {

			fscene::GameObject* parent = getParent()->getParent();
			if (parent != nullptr) {
				m_UIParent = parent->getComponent<UIComponent>();
			}
			else {
				fhelpers::Singleton<fcore::UIManager>::getInstance().addUiList(getParent()->getDepth(), this);
			}
			m_vao->loadUIIntoOpenGL();

			updateMatrix();
			return true;
		}

		void UIComponent::draw2D() {

			glBindVertexArray(m_vao->VAO);
			m_material->use();// pass in 4 matrix
			m_material->loadTransform(m_UITranform);
			// 4 is the size of elements
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);

			m_material->unuse();

			for (fscene::GameObject* obj : getParent()->getChildren())
			{
				UIComponent* UIComp = obj->getComponent<UIComponent>();
				if (!UIComp)
					continue;

				UIComp->draw2D();
			}
		}

		void UIComponent::update() {
			updateMatrix();
		}

		bool UIComponent::shutdown() {
			m_vao->destroy();
			delete(m_vao);
			m_vao = nullptr;

			m_material->destroy();
			delete(m_material);
			m_material = nullptr;
			return true;

		}

		void UIComponent::updateMatrix()
		{
			if (m_isDirty) {
				m_UITranform = fmath::Matrix4::create2Dmatrix(m_offset, m_rolation, m_scale);
				m_isDirty = false;
				if (m_UIParent) {
					//this is for recursion. 
					//UI->updateMatrix();
					this->m_UITranform *= m_UIParent->m_UITranform;
				}
			}
		}


		void UIComponent::AnchorCenter(bool x, bool y)
		{
			if (x)
			{

			}
			if (y)
			{

			}
		}

		void UIComponent::AnchorLeft()
		{
		}

		void UIComponent::AnchorRight()
		{
		}

		void UIComponent::AnchorTop()
		{
		}

		void UIComponent::AnchorBottom()
		{
		}

		void UIComponent::setOffset(const fmath::Vector2 & v)
		{
			m_offset = v;
			makeDirty();
		}

		void UIComponent::setScale(const fmath::Vector2 & s)
		{
			m_scale = s;
			makeDirty();
		}

		void UIComponent::setRolate(float r)
		{
			m_rolation = r;
			makeDirty();
		}

		void UIComponent::setTranform(const fmath::Vector2 & v, float r, const fmath::Vector2 & s)
		{
			m_offset = v;
			m_rolation = r;
			m_scale = s;
			m_isDirty = true;
		}

		void UIComponent::makeDirty()
		{
			for (fscene::GameObject* obj : getParent()->getChildren())
			{
				UIComponent* UIComp = obj->getComponent<UIComponent>();
				if (!UIComp)
					continue;

				UIComp->m_isDirty = true;
			}
		}

	}
}