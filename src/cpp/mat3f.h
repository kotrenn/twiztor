#ifndef __MAT_3F_H_
#define __MAT_3F_H_

#include "mat2f.h"
#include "vec3f.h"

class mat3f
{
	friend class vec2f;
	friend class vec3f;
	friend class mat2f;
	
public:
	mat3f();
	mat3f(float s);
	mat3f(float x11, float x12, float x13,
	      float x21, float x22, float x23,
	      float x31, float x32, float x33);
	mat3f(const float data[3][3]);
	mat3f(const mat2f &rhs);
	mat3f(const mat3f &rhs);

	mat3f &operator=(const mat3f &rhs);

	static mat3f identity3f();
	static mat3f scale3f(float scale);
	static mat3f scale3f(float scaleX, float scaleY, float scaleZ);
	static mat3f rotation3fX(float thetaX);
	static mat3f rotation3fY(float thetaY);
	static mat3f rotation3fZ(float thetaZ);
	static mat3f rotation3f(float theta, float axisX, float axisY, float axisZ);
	static mat3f rotation3f(float theta, const vec3f &axis);

	const mat3f operator+(const mat3f &rhs) const;
	const mat3f operator+=(const mat3f &rhs);
	const mat3f operator-(const mat3f &rhs) const;
	const mat3f operator-=(const mat3f &rhs);

	const mat3f operator*(float rhs) const;
	const mat3f operator*=(float rhs);
	const vec3f operator*(const vec3f &rhs) const;
	const mat3f operator*(const mat3f &rhs) const;
	const mat3f operator*=(const mat3f &rhs);

	const mat3f operator/(float rhs) const;
	const mat3f operator/=(float rhs);
	const mat3f operator/(const mat3f &rhs);
	const mat3f operator/=(const mat3f &rhs);

	bool isSingular() const;
	bool isInvertible() const;

	const mat3f getInverse() const;
	const mat3f invert();

	float getDeterminant() const;

	const mat2f getFoo(int row, int col) const;
	float getCofactor(int row, int col) const;
	
	float getEntry(int row, int col) const { return m_data[row][col]; }

	void setEntry(int row, int col, float value) { m_data[row][col] = value; }
private:
	float m_data[3][3];
};

std::ostream &operator<<(std::ostream &out, const mat3f &rhs);
const mat3f operator*(float lhs, const mat3f &rhs);

#endif
