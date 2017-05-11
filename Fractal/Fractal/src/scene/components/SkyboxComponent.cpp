#include "scene\components\SkyboxComponent.h"
#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"
#include "core\systems\manager\SystemManager.h"
#include <Fractal\include\scene\GameObject.h>
#include <Fractal\include\core\systems\manager\CameraManager.h>
#include <Fractal\include\scene\components\CameraComponent.h>
#include "core\systems\Window.h"
namespace fractal {
	namespace fscene {
		SkyboxComponent::SkyboxComponent(fgraphics::Material* m) :
			Component("Skybox"),
			m_material(m),
			m_vao(new fgraphics::Vao())
		{

		}

		SkyboxComponent::~SkyboxComponent() {

		}

		bool SkyboxComponent::initialize() {
			m_camera = fhelpers::Singleton<fcore::CameraManager>::getInstance().getActiveCamera();

			m_vao->loadSkybox();

			glBindVertexArray(m_vao->VAO);
			m_material->use();
			//load projection matrix			
			m_material->loadProjectionMatrix(fmath::Matrix4::perspective(50.0f, WWIDTH / WHEIGHT, 0.1f, 1000.0f));
			m_material->unuse();

			return true;
		}

		void SkyboxComponent::update() {

		}

		bool SkyboxComponent::shutdown() {
			m_vao->destroy();
			delete m_vao;

			m_vao = nullptr;

			m_material->destroy();
			delete m_material;
			m_material = nullptr;

			return true;
		}

		void SkyboxComponent::draw() const {
			glBindVertexArray(m_vao->VAO);
			m_material->use();
			fmath::Matrix4 viewMatrix = m_camera->getViewMatrix();
			viewMatrix[12] = 0;
			viewMatrix[13] = 0;
			viewMatrix[14] = 0;
		    m_material->loadViewMatrix(viewMatrix);
			glDrawArrays(GL_TRIANGLES, 0, m_vao->indicesSize);
			m_material->unuse();
		}
	}
}