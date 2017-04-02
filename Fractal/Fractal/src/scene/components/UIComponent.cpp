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
			Component("UIComponent"),
			m_material(m), m_offset(fmath::Vector2()), m_rolation(0.0f), m_scale(Vector2(1.0f)), m_vao(new fgraphics::Vao())
		{
			//empty
		}

		UIComponent::~UIComponent() {
			//empty
		}

		bool UIComponent::initialize() {
			fhelpers::Singleton<fcore::UIManager>::getInstance().addUiList(getParent()->getDepth(), this);
			m_vao->loadUIIntoOpenGL();
			return true;
		}

		void UIComponent::draw2D() {
			glBindVertexArray(m_vao->VAO);

			m_material->use();// pass in 4 matrix
			m_material->load2DMatrix(m_offset, m_rolation, m_scale);
			// 4 is the size of elements
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);

			m_material->unuse();
		}

		void UIComponent::update() {
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

	}
}