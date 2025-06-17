#include "Vec3.hpp"
#include <cmath>

Vec3 Vec3::min(const Vec3 &a, const Vec3 &b) {
	return Vec3(
		std::min(a.x, b.x),
		std::min(a.y, b.y),
		std::min(a.z, b.z)
	);
}

Vec3 Vec3::max(const Vec3 &a, const Vec3 &b) {
	return Vec3(
		std::max(a.x, b.x),
		std::max(a.y, b.y),
		std::max(a.z, b.z)
	);
}

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) {}

Vec3::Vec3(const float &value) : x(value), y(value), z(value) {}

Vec3::Vec3(const float &x, const float &y) : x(x), y(y), z(0.0f) {}

Vec3::Vec3(const float &x, const float &y, const float &z) : x(x), y(y), z(z) {}

Vec3::Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {}

Vec3& Vec3::operator=(const Vec3 &other) {
	if (this != &other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return *this;
}

Vec3 Vec3::operator+(const Vec3 &other) const {
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3 &other) const {
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const Vec3 &other) const {
	return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::operator/(const Vec3 &other) const {
	if (other.x == 0.0f || other.y == 0.0f || other.z == 0.0f) {
		throw std::runtime_error("Division by zero in Vec3 division");
	}
	return Vec3(x / other.x, y / other.y, z / other.z);
}

Vec3 Vec3::operator+(const float &value) const {
	return Vec3(x + value, y + value, z + value);
}

Vec3 Vec3::operator-(const float &value) const {
	return Vec3(x - value, y - value, z - value);
}

Vec3 Vec3::operator*(const float &value) const {
	return Vec3(x * value, y * value, z * value);
}

Vec3 Vec3::operator/(const float &value) const {
	if (value == 0.0f) {
		throw std::runtime_error("Division by zero in Vec3 division");
	}
	return Vec3(x / value, y / value, z / value);
}

float Vec3::dot(const Vec3 &other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3 &other) const {
	return Vec3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

Vec3& Vec3::operator+=(const Vec3 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3& Vec3::operator-=(const Vec3 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3 &other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vec3& Vec3::operator/=(const Vec3 &other) {
	if (other.x == 0.0f || other.y == 0.0f || other.z == 0.0f) {
		throw std::runtime_error("Division by zero in Vec3 division");
	}
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vec3& Vec3::operator+=(const float &value) {
	x += value;
	y += value;
	z += value;
	return *this;
}

Vec3& Vec3::operator-=(const float &value) {
	x -= value;
	y -= value;
	z -= value;
	return *this;
}

Vec3& Vec3::operator*=(const float &value) {
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vec3& Vec3::operator/=(const float &value) {
	if (value == 0.0f) {
		throw std::runtime_error("Division by zero in Vec3 division");
	}
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

float Vec3::length() const {
	return std::sqrt(x * x + y * y + z * z);
}

float Vec3::lengthSquared() const {
	return x * x + y * y + z * z;
}

Vec3 Vec3::normalized() const {
	float len = length();
	if (len == 0.0f) {
		throw std::runtime_error("Cannot normalize a zero-length vector");
	}
	return Vec3(x / len, y / len, z / len);
}

Vec3& Vec3::normalize() {
	float len = length();
	if (len == 0.0f) {
		throw std::runtime_error("Cannot normalize a zero-length vector");
	}
	x /= len;
	y /= len;
	z /= len;
	return *this;
}

float Vec3::getX() const {
	return x;
}

float Vec3::getY() const {
	return y;
}

float Vec3::getZ() const {
	return z;
}

void Vec3::setX(const float &x) {
	this->x = x;
}

void Vec3::setY(const float &y) {
	this->y = y;
}

void Vec3::setZ(const float &z) {
	this->z = z;
}

std::ostream& operator<<(std::ostream &os, const Vec3 &vec) {
	os << "Vec3(" << vec.getX() << ", " << vec.getY() << ", " << vec.getZ() << ")";
	return os;
}
