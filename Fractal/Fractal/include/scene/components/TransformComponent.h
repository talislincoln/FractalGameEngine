#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include "scene\Component.h"

#include <FractalMath\Vector.h>

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
			void rotate(float rotation);

			void setPosition(const fmath::Vector3& position);
			void setScale(const fmath::Vector3& scale);
			void setRotation(float angle);

			const fmath::Vector3& getPosition() const;
			const fmath::Vector3& getScale() const;
			float getRotation() const;

			//const Matrix2D& getWorldMatrix() const;

		private:
			bool m_isDirty;

			fmath::Vector3 m_position;
			fmath::Vector3 m_scaling;
			float m_rotation;

			//Matrix2D world_matrix;
		};
	}
}

#endif // !_TRANSFORMCOMPONENT_H
