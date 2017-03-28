#include "core\systems\manager\CameraManager.h"
#include "scene\components\CameraComponent.h"

#include <assert.h>
#include <algorithm> //using for the find_if function, trying to look for a camera

namespace fractal {
	namespace fcore {
		CameraManager::CameraManager() :
			m_activeCamera(nullptr)
		{

		}

		CameraManager::~CameraManager() {

		}

		bool CameraManager::initialize() {
			return true;
		}

		bool CameraManager::shutdown() {
			this->m_cameras.clear();
			return true;
		}

		void CameraManager::setActiveCamera(const std::string& name) {
			//uses a nameless function to check if any of the cameras contains the specified name
			std::vector<fscene::CameraComponent*>::iterator it = std::find_if(this->m_cameras.begin(), this->m_cameras.end(),
				[name](fscene::CameraComponent* camera)
			{
				return name == camera->getName();
			});

			if (it == this->m_cameras.end())
				return;

			if (this->m_activeCamera != nullptr)
				this->m_activeCamera->deactive();
			this->m_activeCamera = (*it);
			this->m_activeCamera->activate();
		}

		void CameraManager::setActiveCamera(fscene::CameraComponent* camera) {
			std::vector<fscene::CameraComponent*>::iterator it = std::find(this->m_cameras.begin(), this->m_cameras.end(), camera);
			if (it == this->m_cameras.end()) {
				//debug: trying to activate a camera that doesn't exist
				return;
			}

			if (this->m_activeCamera != nullptr)
				this->m_activeCamera->deactive();
			this->m_activeCamera = camera;
			this->m_activeCamera->activate();
		}

		fscene::CameraComponent* CameraManager::getActiveCamera() const {
			return m_activeCamera;
		}

		void CameraManager::addCamera(fscene::CameraComponent* camera, bool setActive) {
			//Camera cannot be null
			assert(camera != nullptr);

			//look if the camera has already been added to the list
			std::vector<fscene::CameraComponent*>::iterator it = std::find(this->m_cameras.begin(), this->m_cameras.end(), camera);
			if (it != this->m_cameras.end())
				return;

			//if not added, then add the camera to the end of the array 
			this->m_cameras.push_back(camera);

			//check if should activate the newly added camera
			if (setActive)
			{
				if (this->m_activeCamera != nullptr)
					this->m_activeCamera->deactive();
				this->m_activeCamera = camera;
				this->m_activeCamera->activate();
			}
		}
	}
}