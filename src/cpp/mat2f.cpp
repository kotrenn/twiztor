#include "mat2f.h"

mat2f::mat2f()
	:m_a(0.0),
	 m_b(0.0),
	 m_c(0.0),
	 m_d(0.0)
{
}

mat2f::mat2f(float s)
	:m_a(s),
	 m_b(s),
	 m_c(s),
	 m_d(s)
{
}

mat2f::mat2f(float a, float b, float c, float d)
	:m_a(a),
	 m_b(b),
	 m_c(c),
	 m_d(d)
{
}

mat2f::mat2f(const float data[2][2])
	:m_a(data[0][0]),
	 m_b(data[0][1]),
	 m_c(data[1][0]),
	 m_d(data[1][1])
{
}

mat2f::mat2f(const mat2f &rhs)
	:m_a(rhs.m_a),
	 m_b(rhs.m_b),
	 m_c(rhs.m_c),
	 m_d(rhs.m_d)
{
}

mat2f &mat2f::operator=(const mat2f &rhs)
{
	m_a = rhs.m_a;
	m_b = rhs.m_b;
	m_c = rhs.m_c;
	m_d = rhs.m_d;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const mat2f &rhs)
{
	out.precision(3);
	return out << fixed
	           << "[[" << rhs.getA() << ", " << rhs.getB() << "], ["
	           << rhs.getC() << ", " << rhs.getD() << "]]";
}

mat2f mat2f::identity2f()
{
	mat2f ret(1.0, 0.0,
	          0.0, 1.0);
	return ret;
}

mat2f mat2f::scale2f(float scale)
{
	mat2f ret(scale, 0.0,
	          0.0, scale);
	return ret;
}

mat2f mat2f::scale2f(float scaleX, float scaleY)
{
	mat2f ret(scaleX, 0.0,
	          0.0, scaleY);
	return ret;
}

mat2f mat2f::rotation2f(float theta)
{
	float c = cos(theta);
	float s = sin(theta);
	mat2f ret(c, -s,
	          s, c);
	return ret;
}

const mat2f mat2f::operator+(const mat2f &rhs) const
{
	mat2f ret(m_a + rhs.m_a,
	          m_b + rhs.m_b,
	          m_c + rhs.m_c,
	          m_d + rhs.m_d);
	return ret;
}

const mat2f mat2f::operator+=(const mat2f &rhs)
{
	m_a += rhs.m_a;
	m_b += rhs.m_b;
	m_c += rhs.m_c;
	m_d += rhs.m_d;
	return *this;
}

const mat2f mat2f::operator-(const mat2f &rhs) const
{
	mat2f ret(m_a - rhs.m_a,
	          m_b - rhs.m_b,
	          m_c - rhs.m_c,
	          m_d - rhs.m_d);
	return ret;
}

const mat2f mat2f::operator-=(const mat2f &rhs)
{
	m_a -= rhs.m_a;
	m_b -= rhs.m_b;
	m_c -= rhs.m_c;
	m_d -= rhs.m_d;
	return *this;
}

const mat2f mat2f::operator*(float rhs) const
{
	mat2f ret(m_a * rhs,
	          m_b * rhs,
	          m_c * rhs,
	          m_d * rhs);
	return ret;
}

const mat2f operator*(float lhs, const mat2f &rhs)
{
	mat2f ret(lhs * rhs.getA(),
	          lhs * rhs.getB(),
	          lhs * rhs.getC(),
	          lhs * rhs.getD());
	return ret;
}

const mat2f mat2f::operator*=(float rhs)
{
	m_a *= rhs;
	m_b *= rhs;
	m_c *= rhs;
	m_d *= rhs;
	return *this;
}

const vec2f mat2f::operator*(const vec2f &rhs) const
{
	vec2f ret(m_a * rhs.getX() + m_b * rhs.getY(),
	          m_c * rhs.getX() + m_d * rhs.getY());
	return ret;
}

const mat2f mat2f::operator*(const mat2f &rhs) const
{
	mat2f ret(m_a * rhs.m_a + m_b * rhs.m_c,
	          m_a * rhs.m_b + m_b * rhs.m_d,
	          m_c * rhs.m_a + m_d * rhs.m_c,
	          m_c * rhs.m_b + m_d * rhs.m_d);
	return ret;
}

const mat2f mat2f::operator*=(const mat2f &rhs)
{
	float a = m_a * rhs.m_a + m_b * rhs.m_c;
	float b = m_a * rhs.m_b + m_b * rhs.m_d;
	float c = m_c * rhs.m_a + m_d * rhs.m_c;
	float d = m_c * rhs.m_b + m_d * rhs.m_d;
	m_a = a;
	m_b = b;
	m_c = c;
	m_d = d;
	return *this;
}

const mat2f mat2f::operator/(float rhs) const
{
	mat2f ret(m_a / rhs,
	          m_b / rhs,
	          m_c / rhs,
	          m_d / rhs);
	return ret;
}

const mat2f mat2f::operator/=(float rhs)
{
	m_a /= rhs;
	m_b /= rhs;
	m_c /= rhs;
	m_d /= rhs;
	return *this;
}

const mat2f mat2f::operator/(const mat2f &rhs)
{
	mat2f rhsInverse = rhs.getInverse();
	mat2f ret = *this * rhsInverse;
	return ret;
}

const mat2f mat2f::operator/=(const mat2f &rhs)
{
	mat2f rhsInverse = rhs.getInverse();
	mat2f ret = *this * rhsInverse;
	*this = ret;
	return *this;
}

bool mat2f::isSingular() const
{
	float det = getDeterminant();
	return fabs(det) < EPSILON;
}

bool mat2f::isInvertible() const
{
	return !isSingular();
}

const mat2f mat2f::getInverse() const
{
	float det = getDeterminant();
	mat2f inverse(m_d, -m_b, -m_c, m_a);
	inverse /= det;
	return inverse;
}

const mat2f mat2f::invert()
{
	mat2f inverse = getInverse();
	*this = inverse;
	return *this;
}
