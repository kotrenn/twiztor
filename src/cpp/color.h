#ifndef __COLOR_H_
#define __COLOR_H_

#include "common.h"

class ClampedFloat
{
public:
	// Constructors
	ClampedFloat();
	ClampedFloat(float value);

	// Operators
	const ClampedFloat &operator=(const ClampedFloat &rhs);
	const ClampedFloat &operator=(float rhs);

	// Getters
	float getValue() const { return m_value; }
	const float &getValueRef() const { return m_value; }
	float &getValueRef() { return m_value; }

	// Setters
	void setValue(float value) { m_value = value; ensureClamped(); }
private:
	void ensureClamped(); // Ensure 0.0 <= m_value <= 1.0
	float m_value;
};

class Color
{
public:
	// Constructors
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	Color(const string &name);
	Color(const string &name, float r, float g, float b);
	Color(const string &name, float r, float g, float b, float a);
	Color(const Color &other);

	// Operators
	const Color &operator=(const Color &rhs);
	const float &operator[](int i) const;
	float &operator[](int i);

	// Setters
	void setName(const string &name) { m_name = name; };
	void setR(float r) { m_r = r; }
	void setG(float g) { m_g = g; }
	void setB(float b) { m_b = b; }
	void setA(float a) { m_a = a; }
	void setRGB(float r, float g, float b) { m_r = r; m_g = g; m_b = b; }
	void setRGBA(float r, float g, float b, float a) { m_r = r; m_g = g; m_b = b; m_a = a; }

	// Getters
	string getName() const { return m_name; }
	float getR() const { return m_r.getValue(); }
	float getG() const { return m_g.getValue(); }
	float getB() const { return m_b.getValue(); }
	float getA() const { return m_a.getValue(); }

	// Constants
	static const string sc_DEFAULT_NAME;
	static const float  sc_DEFAULT_RED;
	static const float  sc_DEFAULT_GREEN;
	static const float  sc_DEFAULT_BLUE;
	static const float  sc_DEFAULT_ALPHA;
	
private:
	string m_name;
	ClampedFloat m_r;
	ClampedFloat m_g;
	ClampedFloat m_b;
	ClampedFloat m_a;
};

// More operators
std::ostream &operator<<(std::ostream &out, const Color &rhs);
const Color operator*(float lhs, const Color &rhs);

#endif
