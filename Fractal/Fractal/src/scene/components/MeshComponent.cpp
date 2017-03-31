#include "scene\components\MeshComponent.h"

#include "helpers\Singleton.h"
#include "scene\components\TransformComponent.h"
#include "core\systems\manager\SystemManager.h"
#include <FractalMath\Matrix.h>
#include "scene\GameObject.h"
#include <assert.h>

#include <Fractal\include\core\systems\manager\CameraManager.h>
#include <Fractal\include\scene\objects\CameraObject.h>
namespace fractal {
	namespace fscene {
		using namespace fmath;
		MeshComponent::MeshComponent(fgraphics::MeshData* mesh, fgraphics::Material* m) : 
			Component("MeshComponent"), 
			m_material(m)
		{

			m_vao = new fgraphics::Vao();
			m_vao->loadMeshIntoOpenGL(mesh);
			//empty
		}

		MeshComponent::~MeshComponent() {
			//empty
		}

		bool MeshComponent::initialize() {
			return true;
		}

		void MeshComponent::draw() {
			m_vao->bind();

			m_material->use();// pass in 4 matrix
			
			fscene::CameraComponent* camera = fhelpers::Singleton<fcore::CameraManager>::getInstance().getActiveCamera();

			m_material->loadCamera(camera->getViewMatrix(),
				fmath::Matrix4::perspective(50.0f, 800.0f / 500.0f, 0.1f, 1000.0f),  //get that from camera too?
				this->getParent()->getComponent<TransformComponent>()->getWorldMatrix());
			
			glDrawElements(GL_TRIANGLES, m_vao->indicesSize, GL_UNSIGNED_INT, 0);
			m_vao->unbind();
			m_material->unuse();
		}

		void MeshComponent::update() {
		}

		bool MeshComponent::shutdown() {

			m_vao->destroy();
			delete(m_vao);
			m_vao = nullptr;
			m_material->destroy();
			m_material = nullptr;
			return true;
		}
	}
}