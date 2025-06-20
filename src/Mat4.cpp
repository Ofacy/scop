#include "Mat4.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

Mat4 Mat4::perspective(float fov, float aspect, float near, float far) {
	Mat4 result;
	float tanHalfFov = tan(fov * 0.5f * M_PI / 180.0f); // Convert degrees to radians

	result.elements[0] = 1.0f / (aspect * tanHalfFov);
	result.elements[1] = 0.0f;
	result.elements[2] = 0.0f;
	result.elements[3] = 0.0f;

	result.elements[4] = 0.0f;
	result.elements[5] = 1.0f / tanHalfFov;
	result.elements[6] = 0.0f;
	result.elements[7] = 0.0f;

	result.elements[8] = 0.0f;
	result.elements[9] = 0.0f;
	result.elements[10] = -(far + near) / (far - near);
	result.elements[11] = -1.0f;

	result.elements[12] = 0.0f;
	result.elements[13] = 0.0f;
	result.elements[14] = -(2 * far * near) / (far - near);
	result.elements[15] = 0.0f;

	return result;
}

Mat4 Mat4::lookAt(float eyeX, float eyeY, float eyeZ,
							 float centerX, float centerY, float centerZ,
							 float upX, float upY, float upZ) {
	Mat4 result;
	float forwardX = centerX - eyeX;
	float forwardY = centerY - eyeY;
	float forwardZ = centerZ - eyeZ;

	// Normalize forward vector
	float forwardLength = sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
	if (forwardLength == 0.0f) {
		throw std::runtime_error("Zero length forward vector in lookAt");
	}
	forwardX /= forwardLength;
	forwardY /= forwardLength;
	forwardZ /= forwardLength;

	// Right vector
	float rightX = upY * forwardZ - upZ * forwardY;
	float rightY = upZ * forwardX - upX * forwardZ;
	float rightZ = upX * forwardY - upY * forwardX;

	// Normalize right vector
	float rightLength = sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
	if (rightLength == 0.0f) {
		throw std::runtime_error("Zero length right vector in lookAt");
	}
	rightX /= rightLength;
	rightY /= rightLength;
	rightZ /= rightLength;

	// Recompute up vector
	upX = rightY * forwardZ - rightZ * forwardY;
	upY = rightZ * forwardX - rightX * forwardZ;
	upZ = rightX * forwardY - rightY * forwardX;

	result.setIdentity();
	result.elements[0] = rightX;
	result.elements[1] = upX;
	result.elements[2] = -forwardX;
	result.elements[3] = 0.0f;

	result.elements[4] = rightY;
	result.elements[5] = upY;
	result.elements[6] = -forwardY;
	result.elements[7] = 0.0f;

	result.elements[8] = rightZ;
	result.elements[9] = upZ;
	result.elements[10] = -forwardZ;
	result.elements[11] = 0.0f;

	result.elements[12] = -(rightX * eyeX + rightY * eyeY + rightZ * eyeZ);
	result.elements[13] = -(upX * eyeX + upY * eyeY + upZ * eyeZ);
	result.elements[14] = forwardX * eyeX + forwardY * eyeY + forwardZ * eyeZ;
	result.elements[15] = 1.0f;
	return result;
}

Mat4::Mat4() {
	setIdentity();
}

Mat4::Mat4(const Mat4 &other) {
	for (int i = 0; i < 16; ++i) {
		this->elements[i] = other.elements[i];
	}
}

Mat4::~Mat4() {
	// No dynamic memory to free
}

Mat4 &Mat4::operator=(const Mat4 &other) {
	if (this != &other) {
		for (int i = 0; i < 16; ++i) {
			this->elements[i] = other.elements[i];
		}
	}
	return *this;
}
Mat4 Mat4::operator*(const Mat4 &other) const {
	Mat4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.elements[i * 4 + j] = this->elements[i * 4 + 0] * other.elements[0 * 4 + j] +
			                              this->elements[i * 4 + 1] * other.elements[1 * 4 + j] +
			                              this->elements[i * 4 + 2] * other.elements[2 * 4 + j] +
			                              this->elements[i * 4 + 3] * other.elements[3 * 4 + j];
		}
	}
	return result;
}

Mat4 Mat4::operator+(const Mat4 &other) const {
	Mat4 result;
	for (int i = 0; i < 16; ++i) {
		result.elements[i] = this->elements[i] + other.elements[i];
	}
	return result;
}

Mat4 Mat4::operator-(const Mat4 &other) const {
	Mat4 result;
	for (int i = 0; i < 16; ++i) {
		result.elements[i] = this->elements[i] - other.elements[i];
	}
	return result;
}

Mat4 Mat4::operator*(float scalar) const {
	Mat4 result;
	for (int i = 0; i < 16; ++i) {
		result.elements[i] = this->elements[i] * scalar;
	}
	return result;
}

Mat4 Mat4::operator/(float scalar) const {
	if (scalar == 0.0f) {
		throw std::runtime_error("Division by zero in Mat4 operator/");
	}
	Mat4 result;
	for (int i = 0; i < 16; ++i) {
		result.elements[i] = this->elements[i] / scalar;
	}
	return result;
}

void Mat4::setIdentity() {
	for (int i = 0; i < 16; ++i) {
		this->elements[i] = (i % 5 == 0) ? 1.0f : 0.0f;
	}
}

void Mat4::setZero() {
	for (int i = 0; i < 16; ++i) {
		this->elements[i] = 0.0f;
	}
}

void Mat4::setTranslation(float x, float y, float z) {
	this->elements[12] = x;
	this->elements[13] = y;
	this->elements[14] = z;
}

void Mat4::setTranslation(const Vec3 &translation) {
	this->setTranslation(translation.getX(), translation.getY(), translation.getZ());
}

Vec3 Mat4::getTranslation() const {
	return Vec3(this->elements[12], this->elements[13], this->elements[14]);
}

void Mat4::setRotation(float angle, float x, float y, float z) {
	float rad = angle * M_PI / 180.0f; // Convert degrees to radians
	float c = cos(rad);
	float s = sin(rad);
	float oneMinusC = 1.0f - c;

	this->elements[0] = x * x * oneMinusC + c;
	this->elements[1] = x * y * oneMinusC - z * s;
	this->elements[2] = x * z * oneMinusC + y * s;
	this->elements[3] = 0.0f;

	this->elements[4] = y * x * oneMinusC + z * s;
	this->elements[5] = y * y * oneMinusC + c;
	this->elements[6] = y * z * oneMinusC - x * s;
	this->elements[7] = 0.0f;

	this->elements[8] = z * x * oneMinusC - y * s;
	this->elements[9] = z * y * oneMinusC + x * s;
	this->elements[10] = z * z * oneMinusC + c;
	this->elements[11] = 0.0f;

	this->elements[15] = 1.0f;
}

void Mat4::setRotation(const Vec3 &rotation) {
	// Set rotation using Euler angles
	this->setRotation(rotation.getX(), 1.0f, 0.0f, 0.0f); // Rotate around X
	Mat4 rotY;
	rotY.setRotation(rotation.getY(), 0.0f, 1.0f, 0.0f); // Rotate around Y
	*this = *this * rotY; // Combine rotations
	Mat4 rotZ;
	rotZ.setRotation(rotation.getZ(), 0.0f, 0.0f, 1.0f); // Rotate around Z
	*this = *this * rotZ; // Combine rotations
}

// return the rotation as a direction vector
Vec3 Mat4::getDirection() const {
	Vec3 direction;
	direction.setX(this->elements[2]);
	direction.setY(this->elements[6]);
	direction.setZ(this->elements[10]);
	return direction.normalized();
}

void Mat4::transpose() {
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			std::swap(this->elements[i * 4 + j], this->elements[j * 4 + i]);
		}
	}
}

Mat4 Mat4::getTransposed() const {
	Mat4 result = *this;
	result.transpose();
	return result;
}

const float *Mat4::data() const {
	return this->elements;
}
