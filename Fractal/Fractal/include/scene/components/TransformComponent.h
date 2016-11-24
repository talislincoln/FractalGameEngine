#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include "scene\Component.h"

#include <FractalMath\Quaternion.h>

namespace fractal {
	namespace fscene {
		class TransformComponent : public Component
		{
		public:
			TransformComponent(const std::string& name = "");
			virtual ~TransformComponent();

			virtual bool initialize();
			virtual void update();
			virtual bool shutdown();

			void translate(const fmath::Vector3& translation);
			void scale(const fmath::Vector3& scale);
			void rotate(const fmath::Quaternion rotation);


			// ***** setters and getters ***** //
			inline void setPosition(const fmath::Vector3& position) {
				this->m_isDirty = true;
				this->m_position = position;
			}

			void setScale(const fmath::Vector3& scale) {
				this->m_isDirty = true;
				this->m_scaling = scale;
			}

			void setRotation(const fmath::Quaternion& angle) {
				this->m_isDirty = true;
				this->m_rotation = angle;
			}

			inline const fmath::Vector3& getPosition() const {
				return m_position;
			}
			
			inline const fmath::Vector3& getScale() const {
				return m_scaling;
			}

			inline const fmath::Quaternion& getRotation() const {
				return m_rotation;
			}

			inline const fmath::Matrix4& getWorldMatrix() const {
				return m_worldMatrix;
			}

		private:
			bool m_isDirty;

			fmath::Vector3 m_position;
			fmath::Vector3 m_scaling;
			fmath::Quaternion m_rotation;

			fmath::Matrix4 m_worldMatrix;
		};
	}
}

#endif // !_TRANSFORMCOMPONENT_H
