#pragma once
//#include "Component.h"
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
		inline Transform(Vector3 p = Vector3(0.0f), Quaternion r = Quaternion(), Vector3 s = Vector3(1.0f)) {
			position = p;
			rotate = r;
			scale = s;
		}
		inline const Matrix4 GetTransformM4() const {
			return  Matrix4::scale(scale) * rotate.toMatrix() * Matrix4::translate(position);
		}
		inline const Matrix4 GetInvTransformM4() const {
			return  Matrix4::scale(scale) * rotate.conjugate().toMatrix() * Matrix4::translate(position);
		}
		inline const Vector3 operator*(const Vector3& v) const
		{
			return this->GetTransformM4() * v;
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
			t2.scale = this->scale * t.scale;
			//t2.scale = this->scale;
			return t2;

		}


		//--------------------------------------------------------------------------------------------------
		/*inline const q3HalfSpace q3Mul(const q3Transform& tx, const q3HalfSpace& p)
		{
			Vector3 origin = p.Origin();
			origin = q3Mul(tx, origin);
			Vector3 normal = q3Mul(tx.rotation, p.normal);

			return q3HalfSpace(normal, q3Dot(origin, normal));
		}

		--------------------------------------------------------------------------------------------------
		inline const q3HalfSpace q3Mul(const q3Transform& tx, const Vector3& scale, const q3HalfSpace& p)
		{
			Vector3 origin = p.Origin();
			origin = q3Mul(tx, scale, origin);
			Vector3 normal = q3Mul(tx.rotation, p.normal);

			return q3HalfSpace(normal, q3Dot(origin, normal));
		}
		*/
		/*
		inline const Vector3 mulT(const Vector3& v) const
		{
			return q3Transpose(tx.rotation) * (v - tx.position);
		}

		//--------------------------------------------------------------------------------------------------
		inline const Vector3 q3MulT(const q3Mat3& r, const Vector3& v)
		{
			return q3Transpose(r) * v;
		}

		//--------------------------------------------------------------------------------------------------
		inline const q3Mat3 q3MulT(const q3Mat3& r, const q3Mat3& q)
		{
			return q3Transpose(r) * q;
		}

		//--------------------------------------------------------------------------------------------------
		inline const q3Transform q3MulT(const q3Transform& t, const q3Transform& u)
		{
			q3Transform v;
			v.rotation = q3MulT(t.rotation, u.rotation);
			v.position = q3MulT(t.rotation, u.position - t.position);
			return v;
		}

		//--------------------------------------------------------------------------------------------------
		inline const q3HalfSpace q3MulT(const q3Transform& tx, const q3HalfSpace& p)
		{
			Vector3 origin = p.normal * p.distance;
			origin = q3MulT(tx, origin);
			Vector3 n = q3MulT(tx.rotation, p.normal);
			return q3HalfSpace(n, q3Dot(origin, n));
		} */
	};
}
