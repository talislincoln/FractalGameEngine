#include "scene\components\UIComponent.h"

#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"
#include "core\systems\manager\SystemManager.h"
#include <FractalMath\Matrix.h>
#include "scene\GameObject.h"
#include <assert.h>
namespace fractal {
	namespace fHUD {
		using namespace fmath;
		UIComponent::UIComponent(fgraphics::Material* m) :
			Component("UIComponent"),
			m_material(m)
		{
			//empty
		}

		UIComponent::~UIComponent() {
			//empty
		}

		bool UIComponent::initialize() {
			createVAO();
			storeDataInVAO();
			unbindVAO();
			
			return true;
		}

		void UIComponent::draw() {
			glBindVertexArray(m_vao);

			m_material->use();// pass in 4 matrix
			m_material->load2DMatrix();
			// 4 is the size of elements
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
			glBindVertexArray(0);

			m_material->unuse();
		}

		void UIComponent::update() {
		}

		bool UIComponent::shutdown() {
			glDeleteVertexArrays(1, &m_vao);

			for (GLuint& vbo : m_vbos) {
				glDeleteBuffers(1, &vbo);
			}

			m_vbos.clear();

			m_material->destroy();
			m_material = nullptr;
			return true;
		}

		void UIComponent::createVAO() {
			//first argument specifies the number of arrays to generate
			glGenVertexArrays(1, &m_vao);
			glBindVertexArray(m_vao);
		}

		void UIComponent::storeDataInVAO() {
			//create 1 vbo
			GLuint vbo = 0;
			glGenBuffers(1, &vbo);
			m_vbos.push_back(vbo);
			float quad[] = { -1, 1, -1, -1, 1, 1, 1, -1 };

			//start using this vbo
			glBindBuffer(GL_ARRAY_BUFFER, vbo);

			glBufferData(GL_ARRAY_BUFFER,8, quad, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

			//unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void UIComponent::unbindVAO() const {
			glBindVertexArray(0);
		}
	}
}