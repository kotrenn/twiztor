#include "vec2f.h"

vec2f::vec2f()
	:m_x(0.0),
	 m_y(0.0)
{
}

vec2f::vec2f(float s)
	:m_x(s),
	 m_y(s)
{
}

vec2f::vec2f(float x, float y)
	:m_x(x),
	 m_y(y)
{
}

vec2f::vec2f(const float data[2])
	:m_x(data[0]),
	 m_y(data[1])
{
}

vec2f::vec2f(const vec2f &rhs)
	:m_x(rhs.m_x),
	 m_y(rhs.m_y)
{
}

vec2f &vec2f::operator=(const vec2f &rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const vec2f &rhs)
{
	out.precision(3);
	return out << fixed << "[" << rhs.getX() << ", " << rhs.getY() << "]";
}

const float &vec2f::operator[](int i) const
{
	if (i == 0) return m_x;
	else return m_y;
}

float &vec2f::operator[](int i)
{
	if (i == 0) return m_x;
	else return m_y;
}

const vec2f vec2f::operator+(const vec2f &rhs) const
{
	vec2f ret(m_x + rhs.m_x,
	          m_y + rhs.m_y);
	return ret;
}

const vec2f vec2f::operator+=(const vec2f &rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	return *this;
}

const vec2f vec2f::operator-(const vec2f &rhs) const
{
	vec2f ret(m_x - rhs.m_x,
	          m_y - rhs.m_y);
	return ret;
}

const vec2f vec2f::operator-=(const vec2f &rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	return *this;
}

const vec2f vec2f::operator*(float rhs) const
{
	vec2f ret(m_x * rhs, m_y * rhs);
	return ret;
}

const vec2f operator*(float lhs, const vec2f &rhs)
{
	vec2f ret(lhs * rhs.getX(),
	          lhs * rhs.getY());
	return ret;
}

const vec2f vec2f::operator*=(float rhs)
{
	m_x *= rhs;
	m_y *= rhs;
	return *this;
}

const vec2f vec2f::operator/(float rhs) const
{
	vec2f ret(m_x / rhs, m_y / rhs);
	return ret;
}

const vec2f vec2f::operator/=(float rhs)
{
	m_x /= rhs;
	m_y /= rhs;
	return *this;
}

float vec2f::operator*(const vec2f &rhs) const
{
	float ret = m_x * rhs.m_x + m_y * rhs.m_y;
	return ret;
}

bool vec2f::operator==(const vec2f &rhs) const
{
	bool ret =
		fabs(m_x - rhs.m_x) < EPSILON &&
		fabs(m_y - rhs.m_y) < EPSILON;
	return ret;
}

bool vec2f::operator!=(const vec2f &rhs) const
{
	return !(*this == rhs);
}

float vec2f::getNorm() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

const vec2f vec2f::getUnit() const
{
	float mag = getNorm();
	float retX = 0.0;
	float retY = 0.0;
	if (mag > EPSILON)
	{
		retX = m_x / mag;
		retY = m_y / mag;
	}
	vec2f ret(retX, retY);
	return ret;
}

const vec2f vec2f::normalize()
{
	vec2f unit = getUnit();
	*this = unit;
	return *this;
}
