#pragma once

#include <iostream>

namespace sge{ namespace math {

	struct vec2;
	struct vec4;
	struct mat4;

	struct vec3 {
		float x, y, z;

		vec3();
		vec3(float scalar);
		vec3(const float& x, const float& y, const float& z);
		vec3(const vec2& other);
		vec3(float x, float y);
		vec3(const vec4& other);

		static vec3 up();
		static vec3 down();
		static vec3 left();
		static vec3 right();
		static vec3 zero();

		static vec3 xAxis();
		static vec3 yAxis();
		static vec3 zAxis();

		vec3& add(const vec3& other);
		vec3& subtract(const vec3& other);
		vec3& multiply(const vec3& other);
		vec3& divide(const vec3& other);

		vec3& add(float other);
		vec3& subtract(float other);
		vec3& multiply(float other);
		vec3& divide(float other);

		friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		
		friend vec3 operator+(vec3 left, const vec3& right);
		friend vec3 operator-(vec3 left, const vec3& right);
		friend vec3 operator*(vec3 left, const vec3& right);
		friend vec3 operator/(vec3 left, const vec3& right);

		friend vec3 operator+(vec3 left, float right);
		friend vec3 operator-(vec3 left, float right);
		friend vec3 operator*(vec3 left, float right);
		friend vec3 operator/(vec3 left, float right);

		friend vec3 operator-(const vec3& vector);

		vec3& operator+=(const vec3& other);
		vec3& operator-=(const vec3& other);
		vec3& operator*=(const vec3& other);
		vec3& operator/=(const vec3& other);

		vec3& operator+=(float other);
		vec3& operator-=(float other);
		vec3& operator*=(float other);
		vec3& operator/=(float other);

		bool operator==(const vec3& other);
		bool operator!=(const vec3& other);

		bool operator<(const vec3& other) const;
		bool operator<=(const vec3& other) const;
		bool operator>(const vec3& other) const;
		bool operator>=(const vec3& other) const;

		vec3 cross(const vec3& other) const;
		float dot(const vec3& other) const;

		float magnitude() const;
		vec3 normalize() const;
		float distance(const vec3& other) const;
	};
} }