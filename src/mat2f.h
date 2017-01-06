#ifndef __MAT_2F_H_
#define __MAT_2F_H_

#include "vec2f.h"

class mat2f
{
public:
	mat2f();
	mat2f(float s);
	mat2f(float a, float b, float c, float d);
	mat2f(const float data[2][2]);
	mat2f(const mat2f &rhs);

	mat2f &operator=(const mat2f &rhs);

	static mat2f identity2f();
	static mat2f scale2f(float scale);
	static mat2f scale2f(float scaleX, float scaleY);
	static mat2f rotation2f(float theta);
	
	const mat2f operator+(const mat2f &rhs) const;
	const mat2f operator+=(const mat2f &rhs);
	const mat2f operator-(const mat2f &rhs) const;
	const mat2f operator-=(const mat2f &rhs);

	const mat2f operator*(float rhs) const;
	const mat2f operator*=(float rhs);
	const vec2f operator*(const vec2f &rhs) const;
	const mat2f operator*(const mat2f &rhs) const;
	const mat2f operator*=(const mat2f &rhs);
	
	const mat2f operator/(float rhs) const;
	const mat2f operator/=(float rhs);
	const mat2f operator/(const mat2f &rhs);
	const mat2f operator/=(const mat2f &rhs);

	bool isSingular() const;
	bool isInvertible() const;
	
	const mat2f getInverse() const;
	const mat2f invert();

	float getDeterminant() const { return m_a * m_d - m_b * m_c; }

	float getA() const { return m_a; }
	float getB() const { return m_b; }
	float getC() const { return m_c; }
	float getD() const { return m_d; }

	void setA(float a) { m_a = a; }
	void setB(float b) { m_b = b; }
	void setC(float c) { m_c = c; }
	void setD(float d) { m_d = d; }
private:
	float m_a;
	float m_b;
	float m_c;
	float m_d;
};

std::ostream &operator<<(std::ostream &out, const mat2f &rhs);
const mat2f operator*(float lhs, const mat2f &rhs);


#endif
