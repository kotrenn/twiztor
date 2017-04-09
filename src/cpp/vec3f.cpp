#include "vec3f.h"

vec3f::vec3f()
	:m_x(0.0),
	 m_y(0.0),
	 m_z(0.0)
{
}

vec3f::vec3f(float s)
	:m_x(s),
	 m_y(s),
	 m_z(s)
{
}

vec3f::vec3f(float x, float y, float z)
	:m_x(x),
	 m_y(y),
	 m_z(z)
{
}

vec3f::vec3f(const float data[3])
	:m_x(data[0]),
	 m_y(data[1]),
	 m_z(data[2])
{
}

vec3f::vec3f(const vec3f &rhs)
	:m_x(rhs.m_x),
	 m_y(rhs.m_y),
	 m_z(rhs.m_z)
{
}

vec3f &vec3f::operator=(const vec3f &rhs)
{
	m_x = rhs.m_x;
	m_y = rhs.m_y;
	m_z = rhs.m_z;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const vec3f &rhs)
{
	out.precision(3);
	return out << fixed << "[" << rhs.getX() << ", "
	           << rhs.getY() << ", " << rhs.getZ() << "]";
}

const float &vec3f::operator[](int i) const
{
	if (i == 0) return m_x;
	else if (i == 1) return m_y;
	else return m_z;
}

float &vec3f::operator[](int i)
{
	if (i == 0) return m_x;
	else if (i == 1) return m_y;
	else return m_z;
}

const vec3f vec3f::operator+(const vec3f &rhs) const
{
	vec3f ret(m_x + rhs.m_x,
	          m_y + rhs.m_y,
	          m_z + rhs.m_z);
	return ret;
}

const vec3f vec3f::operator+=(const vec3f &rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	m_z += rhs.m_z;
	return *this;
}

const vec3f vec3f::operator-(const vec3f &rhs) const
{
	vec3f ret(m_x - rhs.m_x,
	          m_y - rhs.m_y,
	          m_z - rhs.m_z);
	return ret;
}

const vec3f vec3f::operator-=(const vec3f &rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	m_z -= rhs.m_z;
	return *this;
}

float vec3f::operator*(const vec3f &rhs) const
{
	float ret
		= m_x * rhs.m_x
		+ m_y * rhs.m_y
		+ m_z * rhs.m_z;
	return ret;
}

const vec3f vec3f::operator*(float rhs) const
{
	vec3f ret(m_x * rhs,
	          m_y * rhs,
	          m_z * rhs);
	return ret;
}

const vec3f vec3f::operator*=(float rhs)
{
	m_x *= rhs;
	m_y *= rhs;
	m_z *= rhs;
	return *this;
}

const vec3f vec3f::cross(const vec3f &rhs) const
{
	vec3f ret(m_y * rhs.m_z - m_z * rhs.m_y,
	          m_z * rhs.m_x - m_x * rhs.m_z,
	          m_x * rhs.m_y - m_y * rhs.m_x);
	return ret;
}

const vec3f vec3f::operator/(float rhs) const
{
	vec3f ret(m_x / rhs,
	          m_y / rhs,
	          m_z / rhs);
	return ret;
}

const vec3f vec3f::operator/=(float rhs)
{
	m_x /= rhs;
	m_y /= rhs;
	m_z /= rhs;
	return *this;
}

bool vec3f::operator==(const vec3f &rhs) const
{
	bool ret =
		fabs(m_x - rhs.m_x) < EPSILON &&
		fabs(m_y - rhs.m_y) < EPSILON &&
		fabs(m_z - rhs.m_z) < EPSILON;
	return ret;
}

bool vec3f::operator!=(const vec3f &rhs) const
{
	return !(*this == rhs);
}

float vec3f::getNorm() const
{
	return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

const vec3f vec3f::getUnit() const
{
	float mag = getNorm();
	float retX = 0.0;
	float retY = 0.0;
	float retZ = 0.0;
	if (mag > EPSILON)
	{
		retX /= mag;
		retY /= mag;
		retZ /= mag;
	}
	vec3f ret(retX, retY, retZ);
	return ret;
}

const vec3f vec3f::normalize()
{
	vec3f unit = getUnit();
	*this = unit;
	return *this;
}
