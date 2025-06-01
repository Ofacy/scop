#ifndef MAT4_HPP
#define MAT4_HPP

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
	void setRotation(float angle, float x, float y, float z);
	void transpose();
	Mat4 getTransposed() const;
	void invert();
	Mat4 getInverted() const;

	const float *data() const;
};

#endif