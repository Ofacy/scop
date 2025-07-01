#ifndef MAT4_HPP
#define MAT4_HPP

# include "Vec3.hpp"

class Mat4 {
private:
	float elements[16];
public:
	static Mat4 perspective(float fov, float aspect, float near, float far);
	static Mat4 lookAt(float eyeX, float eyeY, float eyeZ, 
		float centerX, float centerY, float centerZ, 
		float upX, float upY, float upZ);

	Mat4();
	Mat4(const Mat4 &other);
	~Mat4();

	Mat4 &operator=(const Mat4 &other);
	Mat4 operator*(const Mat4 &other) const;
	Mat4 operator+(const Mat4 &other) const;
	Mat4 operator-(const Mat4 &other) const;
	Mat4 operator*(float scalar) const;
	Mat4 operator/(float scalar) const;
	void setIdentity();
	void setZero();

	void setTranslation(float x, float y, float z);
	void setTranslation(const Vec3 &translation);
	Vec3 getTranslation() const;

	void setRotation(float angle, float x, float y, float z);
	void setRotation(const Vec3 &rotation);
	Vec3 getDirection() const;

	void transpose();
	Mat4 getTransposed() const;

	const float *data() const;
};

#endif