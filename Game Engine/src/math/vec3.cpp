#include "vec3.h"

#include "vec2.h"
#include "vec4.h"
#include "mat4.h"

namespace sge{ namespace math {

	vec3::vec3(): x(0), y(0), z(0) { }

	vec3::vec3(float scalar): x(scalar), y(scalar), z(scalar) { }

	vec3::vec3(const float& x, const float& y, const float& z): x(x), y(y), z(z) { }

	vec3::vec3(const vec2& other): x(other.x), y(other.y), z(0.0f) { }

	vec3::vec3(float x, float y): x(x), y(y), z(0.0f) { }

	vec3::vec3(const vec4& other): x(other.x), y(other.y), z(other.z) { }

	vec3 vec3::up() {
		return vec3(0.0f, 1.0f, 0.0f);
	}

	vec3 vec3::down() {
		return vec3(0.0f, -1.0f, 0.0f);
	}

	vec3 vec3::left() {
		return vec3(-1.0f, 0.0f, 0.0f);
	}

	vec3 vec3::right() {
		return vec3(1.0f, 1.0f, 0.0f);
	}

	vec3 vec3::zero() {
		return vec3(0.0f, 0.0f, 0.0f);
	}

	vec3 vec3::xAxis() {
		return vec3(1.0f, 0.0f, 0.0f);
	}

	vec3 vec3::yAxis() {
		return vec3(0.0f, 1.0f, 0.0f);
	}

	vec3 vec3::zAxis() {
		return vec3(0.0f, 0.0f, 1.0f);
	}

	vec3& vec3::add(const vec3& other){
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	vec3& vec3::subtract(const vec3& other){
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	vec3& vec3::multiply(const vec3& other){
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	vec3& vec3::divide(const vec3& other){
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	vec3& vec3::add(float other) {
		x += other;
		y += other;
		z += other;

		return *this;
	}

	vec3& vec3::subtract(float other) {
		x -= other;
		y -= other;
		z -= other;

		return *this;
	}

	vec3& vec3::multiply(float other) {
		x *= other;
		y *= other;
		z *= other;

		return *this;
	}

	vec3& vec3::divide(float other) {
		x /= other;
		y /= other;
		z /= other;

		return *this;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector){
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

	vec3 operator+(vec3 left, const vec3& right){
		return left.add(right);
	}

	vec3 operator-(vec3 left, const vec3& right){
		return left.subtract(right);
	}

	vec3 operator*(vec3 left, const vec3& right){
		return left.multiply(right);
	}
		
	vec3 operator/(vec3 left, const vec3& right){
		return left.divide(right);
	}

	vec3 operator+(vec3 left, float right) {
		return left.add(right);
	}

	vec3 operator-(vec3 left, float right) {
		return left.subtract(right);
	}

	vec3 operator*(vec3 left, float right) {
		return left.multiply(right);
	}

	vec3 operator/(vec3 left, float right) {
		return left.divide(right);
	}
		
	vec3& vec3::operator+=(const vec3& other){
		return add(other);
	}

	vec3& vec3::operator-=(const vec3& other){
		return subtract(other);
	}

	vec3& vec3::operator*=(const vec3& other){
		return multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other){
		return divide(other);
	}

	vec3& vec3::operator+=(float other) {
		return add(other);
	}

	vec3& vec3::operator-=(float other) {
		return subtract(other);
	}

	vec3& vec3::operator*=(float other) {
		return multiply(other);
	}

	vec3& vec3::operator/=(float other) {
		return divide(other);
	}

	bool vec3::operator==(const vec3& other){
		return x == other.x && y == other.y && z == other.z;
	}

	bool vec3::operator!=(const vec3& other){
		return x != other.x || y != other.y || z != other.z;
	}

	bool vec3::operator<(const vec3& other) const {
		return x < other.x && y < other.y && z < other.z;
	}

	bool vec3::operator<=(const vec3& other) const {
		return x <= other.x && y <= other.y && z <= other.z;
	}

	bool vec3::operator>(const vec3& other) const {
		return x > other.x && y > other.y && z > other.z;
	}

	bool vec3::operator>=(const vec3& other) const {
		return x >= other.x && y >= other.y && z >= other.z;
	}

	vec3 operator-(const vec3& vector) {
		return vec3(-vector.x, -vector.y, -vector.z);
	}

	vec3 vec3::cross(const vec3& other) const {
		return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
	}

	float vec3::dot(const vec3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	float vec3::magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	vec3 vec3::normalize() const {
		float length = magnitude();
		return vec3(x / length, y / length, z / length);
	}

	float vec3::distance(const vec3& other) const {
		float a = x - other.x;
		float b = y - other.y;
		float c = z - other.z;
		return sqrt(a * a + b * b + c * c);
	}
} }