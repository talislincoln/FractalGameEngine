#include "Matrix.h"

namespace fractal {
	namespace fmath {
		///Tested Feb 2 2013 SSF
		Matrix4 Matrix4::rotate(float degrees_, float x_, float y_, float z_) {
			float cosang, sinang, cosm;
			Vector3 rotAxis(x_, y_, z_);
			rotAxis.normalize();
			degrees_ *= DEGREES_TO_RADIANS;
			cosang = cos(degrees_);
			sinang = sin(degrees_);
			cosm = (1.0f - cosang);

			Matrix4 m;

			m[0] = (rotAxis.x * rotAxis.x * cosm) + cosang;
			m[1] = (rotAxis.x * rotAxis.y * cosm) + (rotAxis.z * sinang);
			m[2] = (rotAxis.x * rotAxis.z * cosm) - (rotAxis.y * sinang);
			m[3] = 0.0;
			m[4] = (rotAxis.x * rotAxis.y * cosm) - (rotAxis.z * sinang);
			m[5] = (rotAxis.y * rotAxis.y * cosm) + cosang;
			m[6] = (rotAxis.y * rotAxis.z * cosm) + (rotAxis.x * sinang);
			m[7] = 0.0;
			m[8] = (rotAxis.x * rotAxis.z * cosm) + (rotAxis.y * sinang);
			m[9] = (rotAxis.y * rotAxis.z * cosm) - (rotAxis.x * sinang);
			m[10] = (rotAxis.z * rotAxis.z * cosm) + cosang;
			m[11] = 0.0;
			m[12] = 0.0;
			m[13] = 0.0;
			m[14] = 0.0;
			m[15] = 1.0;

			return m;
		}

		/// As derived in GAME331 
		Matrix4 Matrix4::perspective(const float fovy_, const float aspect_, const float zNear_, const float zFar_) {
			float cot = 1.0f / tan(fovy_* 0.5f * DEGREES_TO_RADIANS);
			/// Don't forget, this looks row centric but it really is a column matrix - right-hand rule rules
			Matrix4 result(cot / aspect_, 0.0f, 0.0f, 0.0f,
				0.0f, cot, 0.0f, 0.0f,
				0.0f, 0.0f, (zNear_ + zFar_) / (zNear_ - zFar_), -1.0,
				0.0, 0.0, (2.0f*zNear_*zFar_) / (zNear_ - zFar_), 0.0);
			return result;
		}


		/// This creates a transform from Normalized Device Coordinates (NDC) to 
		/// screen coordinates. OpenGL uses NDC as			 
		///	              ------------------------------
		///	             /|                           /|
		///	            / |                          / |
		///	           /  |                         /  |
		///	          /   |                        /   |
		///	         /    |                       /    |
		///	        /     |                      /     |
		///	       /      |                     /      |
		///	      /       |                    /       |
		///	     /        |                   /        |
		///	    /         |                  /         |
		///	   /----------------------------/ (1.0,1.0)|
		///	   |          |                 |          |
		///	   |          |                 |          |      +Y
		///	   |          |                 |          | 
		///	   |          |-----------------|----------|      ^
		///	   |         /                  |         /       |
		///	   |        /                   |        /        |       -Z
		///	   |       /                    |       /         |
		///	   |      /                     |      /          |     /
		///	   |     /                      |     /           |    /
		///	   |    /                       |    /            |   /
		///	   |   /                        |   /             |  /
		///	   |  /                         |  /              | /
		///	   | /                          | /               |/
		///	   |/ (-1.0,-1.0)               |/                ----------------> +X
		///	   ------------------------------
		Matrix4 Matrix4::viewportNDC(int width_, int height_) {
			float minZ = 0.0f;
			float maxZ = 1.0f;

			Matrix4 m;
			Matrix4 m1 = scale(1.0f, -1.0f, 1.0f);
			Matrix4 m2 = scale(float(width_) / 2.0f, float(height_) / 2.0f, maxZ - minZ);
			Matrix4 m3 = translate(float(width_) / 2.0f, float(height_) / 2.0f, minZ);

			m = m1 * m2 * m3;

			///This is the slightly faster way but who cares we do it rarely 
			/***
			m[0] = float(width_)/2.0f;
			m[5] = -float(height_)/2.0f;
			m[10] =  maxZ - minZ;
			m[12] = float(width_)/2.0f;
			m[13] = float(height_)/2.0f;
			m[14] = minZ;
			m[15] = 1.0f; ***/

			return m;
		}


		/// 
		Matrix4 Matrix4::orthographic(float xMin_, float xMax_, float yMin_, float yMax_, float zMin_, float zMax_) {
			Matrix4 m;

			Matrix4 m1 = Matrix4::scale(2.0f / (xMax_ - xMin_), 2.0f / (yMax_ - yMin_), -2.0f / (zMax_ - zMin_));
			Matrix4 m2 = Matrix4::translate(-(xMax_ + xMin_) / (xMax_ - xMin_), -(yMax_ + yMin_) / (yMax_ - yMin_), -(zMax_ + zMin_) / (zMax_ - zMin_));
			m = m1 * m2;
			/***
			m[0] = 2.0f / (xMax - xMin);
			m[5] = 2.0f / (yMax - yMin);
			m[10] = -2.0f / (zMax - zMin);
			m[12] = -((xMax + xMin) / (xMax - xMin));
			m[13] = -((yMax + yMin) / (yMax - yMin));
			m[14] = -((zMax + zMin) / (zMax - zMin));
			m[15] = 1.0f;
			***/
			return m;
		}

		/// The orthographic projection matrix is linear and affine but nothing else so there is has no inverse
		/// Therefore, it is labeled singular or non-invertable.
		/// I would still like to back transform from screen space to world space though
		/// Here's my unOrtho - It undoes what the orthographic matrix creates
		/// Multiply screen coordinates by this matrix and you should get x and y world coordinates
		Matrix4 Matrix4::unOrtho(const Matrix4 & ortho) {
			Matrix4 m;
			m[0] = 1.0f / ortho[0];
			m[5] = 1.0f / ortho[5];
			m[10] = 1.0f / ortho[10];
			m[12] = -ortho[12] * m[0];
			m[13] = -ortho[13] * m[5];
			m[14] = -ortho[14] * m[10];
			m[15] = 1.0f;
			return m;
		}

		/// At first glance, it might look like this matrix 
		/// is written left-handed or transposed, it has not. 
		/// Remember how memory is layed out. It is still column based.  
		///Tested Feb 1 2013 SSF  
		Matrix4 Matrix4::translate(float x_, float y_, float z_) {
			return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				x_, y_, z_, 1.0f);
		}
		Matrix4 Matrix4::translate(const Vector3& v) {
			return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				v.x, v.y, v.z, 1.0f);
		}

		Matrix4 Matrix4::scale(float x_, float y_, float z_) {
			return Matrix4(x_, 0.0f, 0.0f, 0.0f,
				0.0f, y_, 0.0f, 0.0f,
				0.0f, 0.0f, z_, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4 Matrix4::scale(const Vector3& s) {
			return Matrix4(s.x, 0.0f, 0.0f, 0.0f,
							0.0f, s.y, 0.0f, 0.0f,
							0.0f, 0.0f, s.z, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
		}

		///Tested Feb 1 2013 SSF
		Matrix4 Matrix4::lookAt(float eyeX, float eyeY, float eyeZ,
			float atX, float atY, float atZ,
			float upX, float upY, float upZ) {

			Vector3 at(atX, atY, atZ);
			Vector3 up(upX, upY, upZ);
			Vector3 eye(eyeX, eyeY, eyeZ);

			Matrix4 result;

			Vector3 forward = (at - eye);
			forward.normalize();
			up.normalize();
			Vector3 side = (forward.cross(up));
			side.normalize();
			up = side.cross(forward);

			result[0] = side.x;
			result[1] = side.y;
			result[2] = side.z;
			result[3] = 0.0;

			result[4] = up.x;
			result[5] = up.y;
			result[6] = up.z;
			result[7] = 0.0;

			result[8] = -forward.x;
			result[9] = -forward.y;
			result[10] = -forward.z;
			result[11] = 0.0;

			result[12] = -(side.dot(eye));
			result[13] = -(up.dot(eye));
			result[14] = (forward.dot(eye));
			result[15] = 1.0;

			return result;
		}

		Matrix4 Matrix4::lookAt(const Vector3& eye, const Vector3& at, const Vector3& up) {
			return lookAt(eye.x, eye.y, eye.z, at.x, at.y, at.z, up.x, up.y, up.z);
		}

		/// Take the transpose of a matrix, swap row with columns 
		Matrix4 Matrix4::transpose(const Matrix4 &m) {
			return Matrix4(m[0 * 4], m[0 * 4 + 1], m[0 * 4 + 2], m[0 * 4 + 3],
				m[1 * 4], m[1 * 4 + 1], m[1 * 4 + 2], m[1 * 4 + 3],
				m[2 * 4], m[2 * 4 + 1], m[2 * 4 + 2], m[2 * 4 + 3],
				m[3 * 4], m[3 * 4 + 1], m[3 * 4 + 2], m[3 * 4 + 3]);
		}

		/// 2x2 inverse is easy, 3x3 is a pain, 4x4 no way, this is tough stuff
		/// Tested 2013
		Matrix4 Matrix4::inverse(const Matrix4 &m) {
			Matrix4 inverseM;
			float determinate;

			inverseM[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
			inverseM[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
			inverseM[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
			inverseM[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
			inverseM[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
			inverseM[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
			inverseM[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
			inverseM[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
			inverseM[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
			inverseM[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
			inverseM[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
			inverseM[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
			inverseM[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
			inverseM[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
			inverseM[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
			inverseM[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

			determinate = m[0] * inverseM[0] + m[1] * inverseM[4] + m[2] * inverseM[8] + m[3] * inverseM[12];

#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
			if (fabs(determinate) < VERY_SMALL) {
				std::string errorMsg("Divide by nearly zero in Matrix4::inverse!");
				throw errorMsg;
			}
#endif
			determinate = 1.0f / determinate;
			for (int i = 0; i < 16; i++) {
				inverseM[i] *= determinate;
			}
			return inverseM;
		}

		Matrix3 Matrix3::outerProduct(const Vector3 &u, const Vector3 &v) {
			return Matrix3(u.x * v.x, u.x * v.y, u.x * v.z,
						u.y * v.x, u.y * v.y, u.y * v.z,
						u.z * v.x, u.z * v.y, u.z * v.z);
		}

		Matrix3 Matrix3::transpose(const Matrix3 &m) {
			return Matrix3(m[0 * 3], m[0 * 3 + 1], m[0 * 3 + 2],
				m[1 * 3], m[1 * 3 + 1], m[1 * 3 + 2],
				m[2 * 3], m[2 * 3 + 1], m[2 * 3 + 2]);
		}
		Matrix3 Matrix3::inverse(const Matrix3 &m) {

			Matrix3 inverseM;
			float determinate;

			/*0*/inverseM[0] = m[4] * m[8] - m[5] * m[7];
			/*1*/inverseM[3] = m[2] * m[7] - m[1] * m[8];
			/*2*/inverseM[6] = m[1] * m[5] - m[2] * m[4];
			/*3*/inverseM[1] = m[5] * m[6] - m[3] * m[8];
			/*4*/inverseM[4] = m[0] * m[8] - m[2] * m[6];
			/*5*/inverseM[7] = m[2] * m[3] - m[0] * m[5];
			/*6*/inverseM[2] = m[3] * m[7] - m[4] * m[6];
			/*7*/inverseM[5] = m[1] * m[6] - m[0] * m[7];
			/*8*/inverseM[8] = m[0] * m[4] - m[1] * m[3];

			determinate = m[0] * inverseM[0] + m[1] * inverseM[3] + m[2] * inverseM[6];
			printf("%f   \n", determinate);
#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
			if (fabs(determinate) < VERY_SMALL) {
				std::string errorMsg("Divide by nearly zero in Matrix4::inverse!");
				throw errorMsg;
			}
#endif
			determinate = 1.0f / determinate;
			for (int i = 0; i < 9; i++) {
				inverseM[i] *= determinate;
			}
			return inverseM;
		}
	}
}