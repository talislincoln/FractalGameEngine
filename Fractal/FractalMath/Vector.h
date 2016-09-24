#ifndef _VECTOR_H
#define _VECTOR_H

namespace fractal {
	namespace fmath {
		struct vec2 {
			float x, y;

			vec2(float x, float y);
		};

		struct vec3 {
			float x, y, z;

			inline vec3(float s = float(0.0));
			inline vec3(const float x, const float y, const float z);
			inline vec3(const vec3& v);

			inline void load(const float x, const float y, const float z);

			inline vec3& add(const vec3& other);
			inline vec3& subtract(const vec3& other);
			inline vec3& multiply(const vec3& other);

			inline float dot(const vec3& other);
			inline const vec3 cross(const vec3& other);
			vec3& normalize();
			const float magnitude();

			inline vec3& operator= (const vec3& other);
			inline const vec3 operator - () const;
			inline const vec3 operator+(const vec3& other) const;
			inline const vec3 operator-(const vec3& other) const;
			inline const vec3 operator*(const vec3& other) const;
			inline const vec3 operator*(const float s) const;
			inline friend const vec3 operator*(const float s, const vec3& other);
			inline const vec3 operator/(const float s) const;

			inline vec3& operator+=(const vec3& other);
			inline vec3& operator-=(const vec3& other);
			inline vec3& operator*=(const vec3& other);
			inline vec3& operator/=(const float s);

			inline bool operator==(const vec3& other) const;
			inline bool operator!=(const vec3& other) const;

			inline const float operator [] (int index) const;
			inline float& operator [] (int index);

			inline operator const float* () const;

			inline operator float* ();

			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		};

		struct vec4 : public vec3 {
			float w;

			inline vec4(const float s = float(0.0f));
			inline vec4(const float x, const float y, const float z, const float w);
			inline vec4(const vec3& other);
			inline vec4(const vec4& other);

			inline void load(const float x, const float y, const float z, const float w);

			inline vec4& add(const vec4& other);
			inline vec4& subtract(const vec4& other);
			inline vec4& multiply(const vec4& other);

			inline float dot(const vec3& other);
			inline float dot(const vec4& other);
			inline const vec3 cross(const vec3& other) = delete;
			vec4& normalize();
			const float magnitude();

			inline vec4& operator= (const vec4& other);
			inline const vec4 operator - () const;
			inline const vec4 operator+(const vec4& other) const;
			inline const vec4 operator-(const vec4& other) const;
			inline const vec4 operator*(const vec4& other) const;
			inline const vec4 operator*(const float s) const;
			inline friend const vec4 operator*(const float s, const vec4& other);
			inline const vec4 operator/(const float s) const;

			inline vec4& operator += (const vec4& other);
			inline vec4& operator -= (const vec4& other);
			inline vec4& operator *= (const vec4& other);
			inline vec4& operator /= (const float s);

			inline bool operator==(const vec4& other) const;
			inline bool operator!=(const vec4& other) const;

			inline operator const float* () const;
			inline operator float* ();

			friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
		};
	}
}

#endif // !_VECTOR_H