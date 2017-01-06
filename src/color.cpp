#include "color.h"

ClampedFloat::ClampedFloat()
	:m_value(0.0)
{
}

ClampedFloat::ClampedFloat(float value)
	:m_value(value)
{
	ensureClamped();
}

const ClampedFloat &ClampedFloat::operator=(const ClampedFloat &rhs)
{
	m_value = rhs.m_value;
	return *this;
}

const ClampedFloat &ClampedFloat::operator=(float rhs)
{
	m_value = rhs;
	ensureClamped();
	return *this;
}

void ClampedFloat::ensureClamped()
{
	if (m_value < 0.0) m_value = 0.0;
	if (m_value > 1.0) m_value = 1.0;
}



const string Color::sc_DEFAULT_NAME  = "undefined-color";
const float  Color::sc_DEFAULT_RED   = 0.0;
const float  Color::sc_DEFAULT_GREEN = 0.0;
const float  Color::sc_DEFAULT_BLUE  = 0.0;
const float  Color::sc_DEFAULT_ALPHA = 1.0;
	
Color::Color()
	:m_name(sc_DEFAULT_NAME),
	 m_r(sc_DEFAULT_RED),
	 m_g(sc_DEFAULT_GREEN),
	 m_b(sc_DEFAULT_BLUE),
	 m_a(sc_DEFAULT_ALPHA)
{
}

Color::Color(float r, float g, float b)
	:m_name(sc_DEFAULT_NAME),
	 m_r(r),
	 m_g(g),
	 m_b(b),
	 m_a(sc_DEFAULT_ALPHA)
{
}

Color::Color(float r, float g, float b, float a)
	:m_name(sc_DEFAULT_NAME),
	 m_r(r),
	 m_g(g),
	 m_b(b),
	 m_a(a)
{
}
	 

Color::Color(const string &name)
	:m_name(name),
	 m_r(sc_DEFAULT_RED),
	 m_g(sc_DEFAULT_GREEN),
	 m_b(sc_DEFAULT_BLUE),
	 m_a(sc_DEFAULT_ALPHA)
{
}

Color::Color(const string &name, float r, float g, float b)
	:m_name(name),
	 m_r(r),
	 m_g(g),
	 m_b(b),
	 m_a(sc_DEFAULT_ALPHA)
{
}

Color::Color(const string &name, float r, float g, float b, float a)
	:m_name(name),
	 m_r(r),
	 m_g(g),
	 m_b(b),
	 m_a(a)
{
}

Color::Color(const Color &other)
	:m_name(other.m_name),
	 m_r(other.m_r),
	 m_g(other.m_g),
	 m_b(other.m_b),
	 m_a(other.m_a)
{
}

const Color &Color::operator=(const Color &rhs)
{
	m_name = rhs.m_name;
	m_r = rhs.m_r;
	m_g = rhs.m_g;
	m_b = rhs.m_b;
	m_a = rhs.m_a;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const Color &rhs)
{
	out.precision(3);
	return out << fixed << "[Color " << rhs.getName() << ": "
	           << rhs.getR() << ", " << rhs.getG() << ", "
	           << rhs.getB() << "; " << rhs.getA() << "]";
}

const float &Color::operator[](int i) const
{
	switch (i)
	{
	case 0: return m_r.getValueRef();
	case 1: return m_g.getValueRef();
	case 2: return m_b.getValueRef();
	case 3: return m_a.getValueRef();
	default: return m_r.getValueRef();
	};
}

float &Color::operator[](int i)
{
	switch (i)
	{
	case 0: return m_r.getValueRef();
	case 1: return m_g.getValueRef();
	case 2: return m_b.getValueRef();
	case 3: return m_a.getValueRef();
	default: return m_r.getValueRef();
	};
}

const Color operator*(float lhs, const Color &rhs)
{
	string name = rhs.getName();
	float r = lhs * rhs.getR();
	float g = lhs * rhs.getG();
	float b = lhs * rhs.getB();
	float a = lhs * rhs.getA();
	Color ret(name, r, g, b, a);
	return ret;
}
