#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include <FractalMath\Math.h>
#include <FractalMath\Matrix.h>
#include <FractalMath\Quaternion.h>

namespace fractal {

	using namespace fmath;
	struct Transform
	{
		Vector3 position;
		Quaternion rotate;
		Vector3 scale;
		inline Transform(Vector3 position = Vector3(0), Quaternion rotate = Quaternion(), Vector3 scale = Vector3(1)) {
			load(position, rotate, scale);
		}
		inline void load(Vector3 position = Vector3(0), Quaternion rotate = Quaternion(), Vector3 scale = Vector3(1)) {
			this->position = position;
			this->rotate = rotate;
			this->scale = scale;
		}
		inline Matrix4 GetTransformM4() const {
			//return Matrix4();
			return  Matrix4::scale(scale) * rotate.toMatrix() * Matrix4::translate(position);
		}
		inline Matrix4 GetInvTransformM4() const {
			return  Matrix4::scale(scale.inverse()) * rotate.inverse().toMatrix() * Matrix4::translate(-position);
		}
		inline Transform& operator = (const Transform& p)
		{
			this->position = p.position;
			this->rotate = p.rotate;
			this->scale = p.scale;
			return *this;
		}
		inline const Point3 operator * (const Point3& p) const
		{
			return this->GetTransformM4() * p;
		}
		inline const Vector3 operator*(const Vector3& v) const
		{
			return this->rotate.rotate(v);
		}
		inline const Vector3 operator/(const Vector3& v) const
		{
			return this->GetInvTransformM4() * v;
		}

		//This is where the error maybe!!!! look out! scale is not working with this function yet!. work on this later.
		inline const Transform operator*(const Transform& t) const
		{
			Transform t2;
			//t2.position = this->rotate.rotate(this->position) + t.position;

			printf("this %f + that %f \n",scale.x, t.scale.x );
			t2.position = t.rotate.rotate(this->position * t.scale) + t.position;
			t2.rotate = t.rotate * this->rotate;// .scaleQuaternion(t.scale);
			//t2.scale = this->scale * t.scale;
			t2.scale = this->scale;
			return t2;

		}
		inline const void addRotate(const Quaternion r)
		{
			this->rotate = this->rotate * r;
		}
		inline const void addtranslate(const Vector3 v)
		{
			this->position += v;
		}
		inline const void addScale(const Vector3 v)
		{
			this->scale *= v;
		}
		inline const float operator [] (int index) const {
			return *(&position.x + index);
		}
		inline float& operator [] (int index) {
			return *(&position.x + index);
		}
		inline operator float* () { return static_cast<float*>(&position.x); }
		inline operator const float* () const { return static_cast<const float*>(&position.x); }
	};
}

#endif // !_TRANSFORM_H