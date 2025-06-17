#ifndef VEC3_HPP
# define VEC3_HPP

# include <iostream>

class Vec3 {
private:
	float x, y, z;
public:
	static Vec3 min(const Vec3 &a, const Vec3 &b);
	static Vec3 max(const Vec3 &a, const Vec3 &b);

	Vec3();
	Vec3(const float &value);
	Vec3(const float &x, const float &y);
	Vec3(const float &x, const float &y, const float &z);
	Vec3(const Vec3 &other);


	Vec3& operator=(const Vec3 &other);
	Vec3 operator+(const Vec3 &other) const;
	Vec3 operator-(const Vec3 &other) const;
	Vec3 operator*(const Vec3 &other) const;
	Vec3 operator/(const Vec3 &other) const;


	Vec3 operator+(const float &value) const;
	Vec3 operator-(const float &value) const;
	Vec3 operator*(const float &value) const;
	Vec3 operator/(const float &value) const;
	float dot(const Vec3 &other) const;
	Vec3 cross(const Vec3 &other) const;
	Vec3& operator+=(const Vec3 &other);
	Vec3& operator-=(const Vec3 &other);
	Vec3& operator*=(const Vec3 &other);
	Vec3& operator/=(const Vec3 &other);


	Vec3& operator+=(const float &value);
	Vec3& operator-=(const float &value);
	Vec3& operator*=(const float &value);
	Vec3& operator/=(const float &value);
	float length() const;
	float lengthSquared() const;
	Vec3 normalized() const;
	Vec3& normalize();
	

	float getX() const;
	float getY() const;
	float getZ() const;

	void setX(const float &x);
	void setY(const float &y);
	void setZ(const float &z);
};

std::ostream& operator<<(std::ostream &os, const Vec3 &vec);

#endif
