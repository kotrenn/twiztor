#ifndef __VEC_2F_H_
#define __VEC_2F_H_

#include "common.h"

#define EPSILON 0.00001

class vec2f
{
public:
	vec2f();
	vec2f(float s);
	vec2f(float x, float y);
	vec2f(const float data[2]);
	vec2f(const vec2f &rhs);
	
	vec2f &operator=(const vec2f &rhs);
	
	const float &operator[](int i) const;
	float &operator[](int i);
	
	const vec2f operator+(const vec2f &rhs) const;
	const vec2f operator+=(const vec2f &rhs);
	const vec2f operator-(const vec2f &rhs) const;
	const vec2f operator-=(const vec2f &rhs);
	
	float operator*(const vec2f &rhs) const;
	const vec2f operator*(float rhs) const;
	const vec2f operator*=(float rhs);
	
	const vec2f operator/(float rhs) const;
	const vec2f operator/=(float rhs);
	
	bool operator==(const vec2f &rhs) const;
	bool operator!=(const vec2f &rhs) const;

	float getNorm() const;
	const vec2f getUnit() const;
	const vec2f normalize();
	
	float getX() const { return m_x; }
	float getY() const { return m_y; }
	
	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
private:
	float m_x;
	float m_y;
};

std::ostream &operator<<(std::ostream &out, const vec2f &rhs);
const vec2f operator*(float lhs, const vec2f &rhs);

#endif
