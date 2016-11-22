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

			void setPosition(const fmath::Vector3& position);
			void setScale(const fmath::Vector3& scale);
			void setRotation(const fmath::Quaternion angle);

			const fmath::Vector3& getPosition() const;
			const fmath::Vector3& getScale() const;
			const fmath::Quaternion& getRotation() const;

			const fmath::Matrix4& getWorldMatrix() const;

		private:
			bool m_isDirty;

			fmath::Vector3 m_position;
			fmath::Vector3 m_scaling;
			fmath::Quaternion m_rotation;

			fmath::Matrix4 world_matrix;
		};
	}
}

#endif // !_TRANSFORMCOMPONENT_H
