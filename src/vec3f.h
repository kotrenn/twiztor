#ifndef __VEC_3F_H_
#define __VEC_3F_H_

#include "vec2f.h"

class vec3f
{
public:
	vec3f();
	vec3f(float s);
	vec3f(float x, float y, float z);
	vec3f(const float data[3]);
	vec3f(const vec3f &rhs);

	vec3f &operator=(const vec3f &rhs);

	const float &operator[](int i) const;
	float &operator[](int i);

	const vec3f operator+(const vec3f &rhs) const;
	const vec3f operator+=(const vec3f &rhs);
	const vec3f operator-(const vec3f &rhs) const;
	const vec3f operator-=(const vec3f &rhs);

	float operator*(const vec3f &rhs) const;
	const vec3f operator*(float rhs) const;
	const vec3f operator*=(float rhs);
	const vec3f cross(const vec3f &rhs) const;

	const vec3f operator/(float rhs) const;
	const vec3f operator/=(float rhs);

	bool operator==(const vec3f &rhs) const;
	bool operator!=(const vec3f &rhs) const;

	float getNorm() const;
	const vec3f getUnit() const;
	const vec3f normalize();

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	float getZ() const { return m_z; }

	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setZ(float z) { m_z = z; }
private:
	float m_x;
	float m_y;
	float m_z;
};

std::ostream &operator<<(std::ostream &out, const vec3f &rhs);
const vec3f operator*(float lhs, const vec3f &rhs);

#endif
