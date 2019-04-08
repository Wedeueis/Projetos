#include "vec2.h"

namespace sge{ namespace math {

	vec2::vec2(): x(0.0f), y(0.0f) {}

	vec2::vec2(float scalar): x(scalar), y(scalar) {}

	vec2::vec2(const float& x, const float& y): x(x), y(y){}

	vec2::vec2(const vec3& v): x(v.x), y(v.y){}

	vec2& vec2::add(const vec2& other){
		x += other.x;
		y += other.y;

		return *this;
	}

	vec2& vec2::subtract(const vec2& other){
		x -= other.x;
		y -= other.y;

		return *this;
	}

	vec2& vec2::multiply(const vec2& other){
		x *= other.x;
		y *= other.y;

		return *this;
	}

	vec2& vec2::divide(const vec2& other){
		x /= other.x;
		y /= other.y;

		return *this;
	}

	vec2& vec2::add(float value) {
		x += value;
		y += value;

		return *this;
	}

	vec2& vec2::subtract(float value) {
		x -= value;
		y -= value;

		return *this;
	}

	vec2& vec2::multiply(float value) {
		x *= value;
		y *= value;

		return *this;
	}

	vec2& vec2::divide(float value) {
		x /= value;
		y /= value;

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const vec2& vector){
		stream << "vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}

	vec2 operator+(vec2 left, const vec2& right){
		return left.add(right);
	}

	vec2 operator-(vec2 left, const vec2& right){
		return left.subtract(right);
	}

	vec2 operator*(vec2 left, const vec2& right){
		return left.multiply(right);
	}
		
	vec2 operator/(vec2 left, const vec2& right){
		return left.divide(right);
	}

	vec2 operator+(vec2 left, float value) {
		return vec2(left.x + value, left.y + value);
	}

	vec2 operator-(vec2 left, float value) {
		return vec2(left.x - value, left.y - value);
	}

	vec2 operator*(vec2 left, float value) {
		return vec2(left.x * value, left.y * value);
	}

	vec2 operator/(vec2 left, float value) {
		return vec2(left.x / value, left.y / value);
	}
		
	vec2& vec2::operator+=(const vec2& other){
		return add(other);
	}

	vec2& vec2::operator-=(const vec2& other){
		return subtract(other);
	}

	vec2& vec2::operator*=(const vec2& other){
		return multiply(other);
	}

	vec2& vec2::operator/=(const vec2& other){
		return divide(other);
	}

	vec2& vec2::operator+=(float value) {
		return add(value);
	}

	vec2& vec2::operator-=(float value) {
		return subtract(value);
	}

	vec2& vec2::operator*=(float value) {
		return multiply(value);
	}

	vec2& vec2::operator/=(float value) {
		return divide(value);
	}

	bool vec2::operator==(const vec2& other){
		return x == other.x && y == other.y;
	}

	bool vec2::operator!=(const vec2& other){
		return x != other.x || y != other.y;
	}

	bool vec2::operator<(const vec2& other) const {
		return x < other.x && y < other.y;
	}

	bool vec2::operator<=(const vec2& other) const {
		return x <= other.x && y <= other.y;
	}

	bool vec2::operator>(const vec2& other) const {
		return x > other.x && y > other.y;
	}

	bool vec2::operator>=(const vec2& other) const {
		return x >= other.x && y >= other.y;
	}

	float vec2::distance(const vec2& other) const {
		float a = x - other.x;
		float b = y - other.y;
		return sqrt(a * a + b * b);
	}

	float vec2::dot(const vec2& other) const {
		return x * other.x + y * other.y;
	}

	float vec2::magnitude() const {
		return sqrt(x * x + y * y);
	}

	vec2 vec2::normalise() const {
		float length = magnitude();
		return vec2(x / length, y / length);
	}

	std::string vec2::toString() const {
		std::stringstream result;
		result << "vec2: (" << x << ", " << y << ")";
		return result.str();
	}
} }