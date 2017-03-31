#ifndef _MATRIX_H
#define _MATRIX_H
#include <iostream>	/// Needed for the printf statement, could have used cin and cout but I have issues.  
#include "Vector.h"

namespace fractal {
	namespace fmath {
		/// These are the default vectors of the eye (camera) according to OpenGL and the right hand rule
		///								+Y	 -Z
		///	                             |  /
		///   origin(0.0f,0.0f,0.0f);    | /
		///   up(0.0f,1.0f,0.0f);        |/_____+X
		///   forward(0.0f,0.0f,-1.0f);  /
		///                             /
		///                           +Z
		///
		class Matrix4 {

			/// Let's just make sure that all is clear about how this matrix is layed out. 

			/// How a matrix is really layed out is pretty much abitrary but we need to agree
			/// and the world has agreed (except for Microsoft) on the right-hand rule. 
			/// First, the 4x4 matrix is really just an array of 16 numbers.  
			/// We need to think of the array as a matrix in the following way
			/// 4x4 matrix - COLUMN MAJOR - The OpenGL, science, physics, mathematics and engineering way. 
			///	0  4  8  12        [0][0]  [1][0]  [2][0]  [3][0]   
			///	1  5  9  13  (or)  [0][1]  [1][1]  [2][1]  [3][1]
			///	2  6  10 14        [0][2]  [1][2]  [2][2]  [3][2]
			///	3  7  11 15        [0][3]  [1][3]  [2][3]  [3][3]
		private:
			float  m[16];
		public:

			/// Now I can use the structure itself as an array.
			/// When overloading the [] operator you need to declair one
			/// to read the array and one to write to the array. 
			///  Returns a const rvalue
			inline const float operator [] (int index) const {
				return *(m + index);
			}

			/// This one is for writing to the structure as if where an array 
			/// it returns a lvalue
			inline float& operator [] (int index) {
				return *(m + index);
			}

			inline Matrix4& operator = (const Matrix4 &m_) {
				this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2]; this->m[3] = m_[3];
				this->m[4] = m_[4]; this->m[5] = m_[5]; this->m[6] = m_[6]; this->m[7] = m_[7];
				this->m[8] = m_[8]; this->m[9] = m_[9]; this->m[10] = m_[10]; this->m[11] = m_[11];
				this->m[12] = m_[12]; this->m[13] = m_[13]; this->m[14] = m_[14]; this->m[15] = m_[15];
				return *this;
			}


			inline Matrix4(float x0, float x1, float x2, float x3,
				float y0, float y1, float y2, float y3,
				float z0, float z1, float z2, float z3,
				float w0, float w1, float w2, float w3) {
				m[0] = x0;   m[4] = y0;   m[8] = z0; m[12] = w0;
				m[1] = x1;   m[5] = y1;   m[9] = z1; m[13] = w1;
				m[2] = x2;   m[6] = y2;   m[10] = z2; m[14] = w2;
				m[3] = x3;	 m[7] = y3;   m[11] = z3; m[15] = w3;
			}

			/// Create the unit matrix probably the most common way of initializing a matrix
			inline Matrix4(const float d = 1.0f) {
				if (d == 1.0f) {
					loadIdentity();
				}
				else {
					m[0] = d;   m[4] = d;   m[8] = d;   m[12] = d;
					m[1] = d;   m[5] = d;   m[9] = d;   m[13] = d;
					m[2] = d;   m[6] = d;   m[10] = d;   m[14] = d;
					m[3] = d;	 m[7] = d;   m[11] = d;	  m[15] = d;
				}
			}


			/// Creates the identity matrix
			inline void loadIdentity() {
				m[0] = 1.0f;   m[4] = 0.0f;   m[8] = 0.0f;   m[12] = 0.0f;
				m[1] = 0.0f;   m[5] = 1.0f;   m[9] = 0.0f;   m[13] = 0.0f;
				m[2] = 0.0f;   m[6] = 0.0f;   m[10] = 1.0f;   m[14] = 0.0f;
				m[3] = 0.0f;   m[7] = 0.0f;   m[11] = 0.0f;   m[15] = 1.0f;
			}



			/// Multiply two 4x4 matricies. 
			/// Grrr, I never liked mulipling maticies - but it needs to be done. 
			inline const Matrix4 operator*(const Matrix4& n) const {
				///Matrix c; /// This is how I did it in 1980
				///for(int i=0;i<4;i++) {
				///		for(int j=0;j<4;j++) {
				///			c[i*4+j] = (m[i*4+0] * n[0*4+j]) + (m[i*4+1] * n[1*4+j]) + (m[i*4+2] * n[2*4+j]) + (m[i*4+3] * n[3*4+j]);	
				///		}
				///}
				/// This approach is about 8 nanoseconds faster, not because I unrolled the loops but because of the constructor, ask me. 
				return Matrix4(m[0 * 4 + 0] * n[0 * 4 + 0] + m[0 * 4 + 1] * n[1 * 4 + 0] + m[0 * 4 + 2] * n[2 * 4 + 0] + m[0 * 4 + 3] * n[3 * 4 + 0],
					m[0 * 4 + 0] * n[0 * 4 + 1] + m[0 * 4 + 1] * n[1 * 4 + 1] + m[0 * 4 + 2] * n[2 * 4 + 1] + m[0 * 4 + 3] * n[3 * 4 + 1],
					m[0 * 4 + 0] * n[0 * 4 + 2] + m[0 * 4 + 1] * n[1 * 4 + 2] + m[0 * 4 + 2] * n[2 * 4 + 2] + m[0 * 4 + 3] * n[3 * 4 + 2],
					m[0 * 4 + 0] * n[0 * 4 + 3] + m[0 * 4 + 1] * n[1 * 4 + 3] + m[0 * 4 + 2] * n[2 * 4 + 3] + m[0 * 4 + 3] * n[3 * 4 + 3],
					m[1 * 4 + 0] * n[0 * 4 + 0] + m[1 * 4 + 1] * n[1 * 4 + 0] + m[1 * 4 + 2] * n[2 * 4 + 0] + m[1 * 4 + 3] * n[3 * 4 + 0],
					m[1 * 4 + 0] * n[0 * 4 + 1] + m[1 * 4 + 1] * n[1 * 4 + 1] + m[1 * 4 + 2] * n[2 * 4 + 1] + m[1 * 4 + 3] * n[3 * 4 + 1],
					m[1 * 4 + 0] * n[0 * 4 + 2] + m[1 * 4 + 1] * n[1 * 4 + 2] + m[1 * 4 + 2] * n[2 * 4 + 2] + m[1 * 4 + 3] * n[3 * 4 + 2],
					m[1 * 4 + 0] * n[0 * 4 + 3] + m[1 * 4 + 1] * n[1 * 4 + 3] + m[1 * 4 + 2] * n[2 * 4 + 3] + m[1 * 4 + 3] * n[3 * 4 + 3],
					m[2 * 4 + 0] * n[0 * 4 + 0] + m[2 * 4 + 1] * n[1 * 4 + 0] + m[2 * 4 + 2] * n[2 * 4 + 0] + m[2 * 4 + 3] * n[3 * 4 + 0],
					m[2 * 4 + 0] * n[0 * 4 + 1] + m[2 * 4 + 1] * n[1 * 4 + 1] + m[2 * 4 + 2] * n[2 * 4 + 1] + m[2 * 4 + 3] * n[3 * 4 + 1],
					m[2 * 4 + 0] * n[0 * 4 + 2] + m[2 * 4 + 1] * n[1 * 4 + 2] + m[2 * 4 + 2] * n[2 * 4 + 2] + m[2 * 4 + 3] * n[3 * 4 + 2],
					m[2 * 4 + 0] * n[0 * 4 + 3] + m[2 * 4 + 1] * n[1 * 4 + 3] + m[2 * 4 + 2] * n[2 * 4 + 3] + m[2 * 4 + 3] * n[3 * 4 + 3],
					m[3 * 4 + 0] * n[0 * 4 + 0] + m[3 * 4 + 1] * n[1 * 4 + 0] + m[3 * 4 + 2] * n[2 * 4 + 0] + m[3 * 4 + 3] * n[3 * 4 + 0],
					m[3 * 4 + 0] * n[0 * 4 + 1] + m[3 * 4 + 1] * n[1 * 4 + 1] + m[3 * 4 + 2] * n[2 * 4 + 1] + m[3 * 4 + 3] * n[3 * 4 + 1],
					m[3 * 4 + 0] * n[0 * 4 + 2] + m[3 * 4 + 1] * n[1 * 4 + 2] + m[3 * 4 + 2] * n[2 * 4 + 2] + m[3 * 4 + 3] * n[3 * 4 + 2],
					m[3 * 4 + 0] * n[0 * 4 + 3] + m[3 * 4 + 1] * n[1 * 4 + 3] + m[3 * 4 + 2] * n[2 * 4 + 3] + m[3 * 4 + 3] * n[3 * 4 + 3]);

			}
			/// Multipling a matrix by itself is probably the most commom
			/// ("this" is the address of the matrix. "*this" de-references that address
			inline Matrix4& operator*=(const Matrix4& n) {
				*this = *this * n;
				return *this;
			}

			/// Multiply a Vec4 by this matrix and return the resulting vector
			inline Vector4 operator* (const Vector4& v) const {
				float x = v.x * m[0] + v.y * m[4] + v.z * m[8] + v.w * m[12];
				float y = v.x * m[1] + v.y * m[5] + v.z * m[9] + v.w * m[13];
				float z = v.x * m[2] + v.y * m[6] + v.z * m[10] + v.w * m[14];
				float w = v.x * m[3] + v.y * m[7] + v.z * m[11] + v.w * m[15];
				return Vector4(x, y, z, w);
			}
			inline friend std::ostream& operator<<(std::ostream& stream, const Matrix4& Matrix) {
				stream << "|" << Matrix[0] << "  " << Matrix[4] << "  " << Matrix[8] << "  " << Matrix[12] << "| \n"
					<< "|" << Matrix[1] << "  " << Matrix[5] << "  " << Matrix[9] << "  " << Matrix[13] << "| \n"
					<< "|" << Matrix[2] << "  " << Matrix[6] << "  " << Matrix[10] << "  " << Matrix[14] << "| \n"
					<< "|" << Matrix[3] << "  " << Matrix[7] << "  " << Matrix[11] << "  " << Matrix[15] << "| \n\n";

				return stream;
			}

			inline void print() const { /// Print them in column form (right-hand rule)
				printf("%1.3f\t %1.3f\t %1.3f\t %1.3f\n%1.3f\t %1.3f\t %1.3f\t %1.3f\n%1.3f\t %1.3f\t %1.3f\t %1.3f\n%1.3f\t %1.3f\t %1.3f\t %1.3f\n\n",
					m[0], m[4], m[8], m[12],
					m[1], m[5], m[9], m[13],
					m[2], m[6], m[10], m[14],
					m[3], m[7], m[11], m[15]);
			}

			/// These allow me convert from type Matrix to const float * without issues
			inline operator float* () { return static_cast<float*>(&m[0]); }
			inline operator const float* () const { return static_cast<const float*>(&m[0]); }


			static Matrix4 create2Dmatrix(const Vector2& translate = Vector2(), float degree = 0, const Vector2& scale  = Vector2(1.0f));
			static Matrix4 rotate(const float degrees_, const float x_, const float y_, const float z_);
			static Matrix4 rotate(float degrees_, const Vector3& v);
			static Matrix4 translate(const float x_, const float y_, const float z_);
			static Matrix4 translate(const Vector3& v);
			static Matrix4 scale(const float x_, const float y_, const float z_);
			static Matrix4 scale(const Vector3& s);
			static Matrix4 perspective(const float fovy_, const float aspect_, const float zNear_, const float zFar_);
			static Matrix4 viewportNDC(const int width_, const int height_);
			static Matrix4 orthographic(const float xMin_, const float xMax_,
				const float yMin_, const float yMax_,
				const float zMin_, const float zMax_);

			static Matrix4 unOrtho(const Matrix4 & ortho);

			static Matrix4 lookAt(const float eyeX_, const float eyeY_, const float eyeZ_,
				const float atX_, const float atY_, const float atZ_,
				const float upX_, const float upY_, const float upZ_);

			static Matrix4 lookAt(const Vector3& eye, const Vector3& at, const Vector3& up);

			static Matrix4 transpose(const Matrix4 &m);

			static Matrix4 inverse(const Matrix4 &m);

		};


		class Matrix3 {
			/// 3x3 matrix - COLUMN MAJOR 
			///	0	3	6			
			///	1	4	7	 
			///	2	5	8			

		private:
			float  m[9];

		public:

			/// Now I can use the structure itself as an array.
			/// When overloading the [] operator you need to declair one
			/// to read the array and one to write to the array. 
			///  Returns a const rvalue
			inline const float operator [] (int index) const {
				return *(m + index);
			}

			/// This one is for writing to the structure as if where an array 
			/// it returns a lvalue
			inline float& operator [] (int index) {
				return *(m + index);
			}

			inline Matrix3& operator = (const Matrix3 &m_) {
				this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2];
				this->m[3] = m_[3]; this->m[4] = m_[4]; this->m[5] = m_[5];
				this->m[6] = m_[6]; this->m[7] = m_[7]; this->m[8] = m_[8];
				return *this;
			}
			/// Extracts the inner 3x3 from a 4x4 matrix
			/// using the assignment operator
			inline Matrix3& operator = (const Matrix4 &m_) {
				this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2];
				this->m[3] = m_[4]; this->m[4] = m_[5]; this->m[5] = m_[6];
				this->m[6] = m_[8]; this->m[7] = m_[9]; this->m[8] = m_[10];
				return *this;
			}

			inline Matrix3 operator + (const Matrix3 &m_) const {
				return Matrix3(m[0] + m_.m[0], m[1] + m_.m[1], m[2] + m_.m[2],
					m[3] + m_.m[3], m[4] + m_.m[4], m[5] + m_.m[5],
					m[6] + m_.m[6], m[7] + m_.m[7], m[8] + m_.m[8]);
			}
			inline Matrix3 operator * (const float f) const {
				return Matrix3(m[0] *f, m[1] * f, m[2] * f,
					m[3] * f, m[4] * f, m[5] * f,
					m[6] * f, m[7] * f, m[8] * f);
			}
			inline Matrix3& operator *= (const float f) {
				*this = *this * f;
				return *this;
			}
			inline Matrix3& operator *= (const Matrix3 &m_) {
				*this = *this * m_;
				return *this;
			}
			inline Matrix3& operator += (const Matrix3 &m_) {
				*this = *this + m_;
				return *this;
			}
			inline Vector3 operator * (const Vector3 v) const {
				float x = v.x * m[0] + v.y * m[3] + v.z * m[6];
				float y = v.x * m[1] + v.y * m[4] + v.z * m[7];
				float z = v.x * m[2] + v.y * m[5] + v.z * m[8];
				return Vector3(x, y, z);
			}
			inline Matrix3 operator * (const Matrix3& m_) const {
				return Matrix3(m[0] * m_[0] + m[3] * m_[1] + m[6] * m_[2],
					m[1] * m_[0] + m[4] * m_[1] + m[7] * m_[2],
					m[2] * m_[0] + m[5] * m_[1] + m[8] * m_[2],
					m[0] * m_[3] + m[3] * m_[4] + m[6] * m_[5],
					m[1] * m_[3] + m[4] * m_[4] + m[7] * m_[5],
					m[2] * m_[3] + m[5] * m_[4] + m[8] * m_[5],
					m[0] * m_[6] + m[3] * m_[7] + m[6] * m_[8],
					m[1] * m_[6] + m[4] * m_[7] + m[7] * m_[8],
					m[2] * m_[6] + m[5] * m_[7] + m[8] * m_[8]
				);
			}
			inline Matrix3 operator - (const Matrix3 &m_) const {
				return Matrix3(m[0] - m_.m[0], m[1] - m_.m[1], m[2] - m_.m[2],
					m[3] - m_.m[3], m[4] - m_.m[4], m[5] - m_.m[5],
					m[6] - m_.m[6], m[7] - m_.m[7], m[8] - m_.m[8]);
			}

			inline Matrix3& operator -= (const Matrix3 &m_){
				*this = *this - m_;
				return *this;
			}
			/// 
			inline Matrix3(const Matrix4 &m_) {
				this->m[0] = m_[0]; this->m[1] = m_[1]; this->m[2] = m_[2];
				this->m[3] = m_[4]; this->m[4] = m_[5]; this->m[5] = m_[6];
				this->m[6] = m_[8]; this->m[7] = m_[9]; this->m[8] = m_[10];
			}

			/// Constuctors
			
 			inline Matrix3(float xx, float yx, float zx,
				float xy, float yy, float zy,
				float xz, float yz, float zz) {
				m[0] = xx;   m[3] = xy;   m[6] = xz;
				m[1] = yx;   m[4] = yy;   m[7] = yz;
				m[2] = zx;   m[5] = zy;   m[8] = zz;
			}

			/// Create the unit matrix probably the most common way of initializing a matrix
			inline Matrix3(const float d = 1.0f) {
				if (d == 1.0f) {
					loadIdentity();
				}
				else {
					m[0] = d;   m[3] = d;   m[6] = d;
					m[1] = d;   m[4] = d;   m[7] = d;
					m[2] = d;   m[5] = d;   m[8] = d;
				}
			}
			inline Matrix3(const float x, const float y, const float z) {
				m[0] = x;   m[3] = 0;   m[6] = 0;
				m[1] = 0;   m[4] = y;   m[7] = 0;
				m[2] = 0;   m[5] = 0;   m[8] = z;
			}
			inline void freezeRotate(const bool x, const bool y, const bool z) {
				if (x) {
					m[0] = 0;   m[3] = 0;   m[6] = 0;
				}
				if (y) {
					m[1] = 0;   m[4] = 0;   m[7] = 0;
				}
				if (z) {
					m[2] = 0;   m[5] = 0;   m[8] = 0;
				}
			}

			/// Creates the identity matrix
			inline void loadIdentity() {
				m[0] = 1.0f;   m[3] = 0.0f;   m[6] = 0.0f;
				m[1] = 0.0f;   m[4] = 1.0f;   m[7] = 0.0f;
				m[2] = 0.0f;   m[5] = 0.0f;   m[8] = 1.0f;
			}


			inline friend std::ostream& operator<<(std::ostream& stream, const Matrix3& Matrix) {
				stream << "|" << Matrix[0] << "  " << Matrix[3] << "  " << Matrix[6] << "| \n"
					<< "|" << Matrix[1] << "  " << Matrix[4] << "  " << Matrix[7] << "| \n"
					<< "|" << Matrix[2] << "  " << Matrix[5] << "  " << Matrix[8] << "| \n\n";

				return stream;
			}

			inline void print() const { /// Print them in column form (right-hand rule)
				printf("%1.3f\t %1.3f\t %1.3f\n%1.3f\t %1.3f\t %1.3f\n%1.3f\t %1.3f\t %1.3f\n\n",
					m[0], m[3], m[6],
					m[1], m[4], m[7],
					m[2], m[5], m[8]);
			}



			/// These allow me convert from type Matrix to const float * without issues
			inline operator float* () { return static_cast<float*>(&m[0]); }
			inline operator const float* () const { return static_cast<const float*>(&m[0]); }


			///static function;
			static Matrix3 outerProduct(const Vector3 &u, const Vector3 &v);
			static Matrix3 transpose(const Matrix3 &m);
			static Matrix3 inverse(const Matrix3 &m);
		};
	}
}
#endif