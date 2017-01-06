#include "mat3f.h"

mat3f::mat3f()
	:m_data{
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 },
	{ 0.0, 0.0, 0.0 }}
{
}

mat3f::mat3f(float s)
	:m_data{
	{ s, s, s },
	{ s, s, s },
	{ s, s, s }}
{
}

mat3f::mat3f(float x11, float x12, float x13,
             float x21, float x22, float x23,
             float x31, float x32, float x33)
	:m_data{
	{ x11, x12, x13 },
	{ x21, x22, x23 },
	{ x31, x32, x33 }}
{
}

mat3f::mat3f(const float data[3][3])
	:m_data{
	{ data[0][0], data[0][1], data[0][2] },
	{ data[1][0], data[1][1], data[1][2] },
	{ data[2][0], data[2][1], data[2][2] }}
{
}

mat3f::mat3f(const mat3f &rhs)
	:m_data{
	{ rhs.m_data[0][0], rhs.m_data[0][1], rhs.m_data[0][2] },
	{ rhs.m_data[1][0], rhs.m_data[1][1], rhs.m_data[1][2] },
	{ rhs.m_data[2][0], rhs.m_data[2][1], rhs.m_data[2][2] }}
{
}

mat3f &mat3f::operator=(const mat3f &rhs)
{
	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			m_data[row][col] = rhs.m_data[row][col];
	
	return *this;
}

std::ostream &operator<<(std::ostream &out, const mat3f &rhs)
{
	out.precision(3);
	return out << fixed
	           << "[["
	           << rhs.getEntry(0, 0) << ", " << rhs.getEntry(0, 1) << ", " << rhs.getEntry(0, 2)
	           << "], ["
	           << rhs.getEntry(1, 0) << ", " << rhs.getEntry(1, 1) << ", " << rhs.getEntry(1, 2)
	           << "], ["
	           << rhs.getEntry(2, 0) << ", " << rhs.getEntry(2, 1) << ", " << rhs.getEntry(2, 2)
	           << "]]";
}

mat3f mat3f::identity3f()
{
	mat3f ret(1.0, 0.0, 0.0,
	          0.0, 1.0, 0.0,
	          0.0, 0.0, 1.0);
	return ret;
}

mat3f mat3f::scale3f(float scale)
{
	mat3f ret(scale, 0.0, 0.0,
	          0.0, scale, 0.0,
	          0.0, 0.0, scale);
	return ret;
}

mat3f mat3f::scale3f(float scaleX, float scaleY, float scaleZ)
{
	mat3f ret(scaleX, 0.0, 0.0,
	          0.0, scaleY, 0.0,
	          0.0, 0.0, scaleZ);
	return ret;
}

mat3f mat3f::rotation3fX(float thetaX)
{
	float c = cos(thetaX);
	float s = sin(thetaX);

	mat3f ret(1.0, 0.0, 0.0,
	          0.0, c,   -s,
	          0.0, s,   c);

	return ret;
}

mat3f mat3f::rotation3fY(float thetaY)
{
	float c = cos(thetaY);
	float s = sin(thetaY);

	mat3f ret(c,   0.0, s,
	          0.0, 1.0, 0.0,
	          -s,  0.0, c);

	return ret;
}

mat3f mat3f::rotation3fZ(float thetaZ)
{
	float c = cos(thetaZ);
	float s = sin(thetaZ);
	
	mat3f ret(c,   -s,  0.0,
	          s,   c,   0.0,
	          0.0, 0.0, 1.0);
	
	return ret;
}

mat3f mat3f::rotation3f(float theta, float axisX, float axisY, float axisZ)
{
	return rotation3f(theta, vec3f(axisX, axisY, axisZ));
}

mat3f mat3f::rotation3f(float theta, const vec3f &axis)
{
	vec3f unit = axis.getUnit();

	float ux = unit.getX();
	float uy = unit.getY();
	float uz = unit.getZ();

	float c = cos(theta);
	float s = sin(theta);

	mat3f ret(c + (1 - c) * ux * ux,      // ret_11
	          (1 - c) * ux * uy - s * uz, // ret_12
	          (1 - c) * ux * uz + s * uy, // ret_13
	          (1 - c) * ux * uy + s * uz, // ret_21
	          c + (1 - c) * uy * uy,      // ret_22
	          (1 - c) * uy * uz - s * ux, // ret_23
	          (1 - c) * ux * uz - s * uy, // ret_31
	          (1 - c) * uy * uz + s * ux, // ret_32
	          c + (1 - c) * uz * uz);     // ret_33

	return ret;
}

const mat3f mat3f::operator+(const mat3f &rhs) const
{
	float data[3][3];

	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			data[row][col] = m_data[row][col] + rhs.m_data[row][col];
	
	mat3f ret(data);
	return ret;
}

const mat3f mat3f::operator+=(const mat3f &rhs)
{
	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			m_data[row][col] += rhs.m_data[row][col];

	return *this;
}

const mat3f mat3f::operator-(const mat3f &rhs) const
{
	float data[3][3];

	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			data[row][col] = m_data[row][col] - rhs.m_data[row][col];

	mat3f ret(data);
	return ret;
}

const mat3f mat3f::operator-=(const mat3f &rhs)
{
	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			m_data[row][col] -= rhs.m_data[row][col];

	return *this;
}

const mat3f mat3f::operator*(float rhs) const
{
	float data[3][3];

	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			data[row][col] = m_data[row][col] * rhs;

	mat3f ret(data);
	return ret;
}

const mat3f operator*(float lhs, const mat3f &rhs)
{
	float data[3][3];

	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			data[row][col] = lhs * rhs.getEntry(row, col);

	mat3f ret(data);
	return ret;
}

const mat3f mat3f::operator*=(float rhs)
{
	for (int row = 0; row < 3; ++row)
		for (int col = 0; col < 3; ++col)
			m_data[row][col] *= rhs;

	return *this;
}

const vec3f mat3f::operator*(const vec3f &rhs) const
{
	float data[3];

	for (int i = 0; i < 3; ++i)
	{
		data[i] = 0.0;
		for (int k = 0; k < 3; ++k)
			data[i] += m_data[i][k] * rhs[k];
	}

	vec3f ret(data);
	return ret;
}

const mat3f mat3f::operator*(const mat3f &rhs) const
{
	float data[3][3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			data[i][j] = 0.0;
			for (int k = 0; k < 3; ++k)
				data[i][j] += m_data[i][k] * rhs.m_data[k][j];
		}

	mat3f ret(data);
	return ret;
}

const mat3f mat3f::operator*=(const mat3f &rhs)
{
	float data[3][3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
		{
			data[i][j] = 0.0;
			for (int k = 0; k < 3; ++k)
				data[i][j] += m_data[i][k] * rhs.m_data[k][j];
		}

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			m_data[i][j] = data[i][j];

	return *this;
}

const mat3f mat3f::operator/(float rhs) const
{
	float data[3][3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = m_data[i][j] / rhs;
	
	mat3f ret(data);
	return ret;
}

const mat3f mat3f::operator/=(float rhs)
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			m_data[i][j] /= rhs;
	
	return *this;
}

bool mat3f::isSingular() const
{
	float det = getDeterminant();
	return fabs(det) < EPSILON;
}

bool mat3f::isInvertible() const
{
	return !isSingular();
}

const mat3f mat3f::getInverse() const
{
	float det = getDeterminant();

	float data[3][3];
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			data[i][j] = getCofactor(j, i) / det;

	mat3f ret(data);
	return ret;
}

const mat3f mat3f::invert()
{
	mat3f inverse = getInverse();
	*this = inverse;
	return *this;
}

float mat3f::getDeterminant() const
{
	float a11 = m_data[0][0];
	float a12 = m_data[0][1];
	float a13 = m_data[0][2];
	float a21 = m_data[1][0];
	float a22 = m_data[1][1];
	float a23 = m_data[1][2];
	float a31 = m_data[2][0];
	float a32 = m_data[2][1];
	float a33 = m_data[2][2];

	float ret =
		a11 * (a22 * a33 - a23 * a32) -
		a12 * (a21 * a33 - a23 * a31) +
		a13 * (a21 * a32 - a22 * a31);
	return ret;
}

const mat2f mat3f::getFoo(int row, int col) const
{
	float data[2][2];
	for (int i = 0; i < 3; ++i)
	{
		if (i == row) continue;
		int r = i;
		if (i > row) --r;
		for (int j = 0; j < 3; ++j)
		{
			if (j == row) continue;
			int c = j;
			if (j > col) --c;
			data[r][c] = m_data[i][j];
		}
	}

	mat2f ret(data);
	return data;
}

float mat3f::getCofactor(int row, int col) const
{
	int sign = pow(-1, row + col);
	mat2f mat = getFoo(row, col);
	return sign * mat.getDeterminant();
}
