#include "vec4.h"

Vec4::Vec4()
{
}

Vec4::Vec4(double p_x, double p_y, double p_z)
{
	m_x = p_x;
	m_y = p_y;
	m_z = p_z;
	m_w = norm();
}

Vec4::Vec4(const Vec4& p_cpy)
{
	m_x = p_cpy.m_x;
	m_y = p_cpy.m_y;
	m_z = p_cpy.m_z;
	m_w = p_cpy.m_w;
}

Vec4::~Vec4()
{
}

bool Vec4::isEqual(const Vec4& p_b) const
{
	if (m_x == p_b.m_x && m_y == p_b.m_y && m_z == p_b.m_z && m_w == p_b.m_w)
		return true;
	return false;
}

void Vec4::operator+=(const Vec4& p_b)
{
	m_x += p_b.m_x;
	m_y += p_b.m_y;
	m_z += p_b.m_z;
	m_w = norm();
}

void Vec4::operator-=(const Vec4& p_b)
{
	m_x -= p_b.m_x;
	m_y -= p_b.m_y;
	m_z -= p_b.m_z;
	m_w = norm();
}

void Vec4::operator*=(const Vec4& p_b) // dot product
{
	double x = m_y * p_b.m_z - m_z * p_b.m_y;
	double y = m_z * p_b.m_x - m_x * p_b.m_z;
	double z = m_x * p_b.m_y - m_y * p_b.m_x;

	m_x = x;
	m_y = y;
	m_z = z;
	m_w = norm();
}

void Vec4::operator*=(double p_b)
{
	m_x *= p_b;
	m_y *= p_b;
	m_z *= p_b;
	m_w = norm();
}

void Vec4::operator/=(double p_b)
{
	m_x /= p_b;
	m_y /= p_b;
	m_z /= p_b;
	m_w = norm();
}

bool operator==(const Vec4& p_a, const Vec4& p_b)
{
	return p_a.isEqual(p_b);
}

bool operator!=(const Vec4& p_a, const Vec4& p_b)
{
	return !p_a.isEqual(p_b);
}

Vec4 operator+(const Vec4& p_a, const Vec4& p_b)
{
	Vec4 cpy = Vec4(p_a);
	cpy += p_b;
	return cpy;
}

Vec4 operator-(const Vec4& p_a, const Vec4& p_b)
{
	Vec4 cpy = Vec4(p_a);
	cpy -= p_b;
	return cpy;
}

Vec4 operator*(const Vec4& p_a, const Vec4& p_b) // cross product
{
	Vec4 cpy = Vec4(p_a);
	cpy *= p_b;
	return cpy;
}

Vec4 operator*(const Vec4& p_a, double p_b)
{
	Vec4 cpy = Vec4(p_a);
	cpy *= p_b;
	return cpy;
}

Vec4 operator*(double p_a, const Vec4& p_b)
{
	return p_b * p_a;
}

Vec4 operator/(const Vec4& p_a, double p_b)
{
	Vec4 cpy = Vec4(p_a);
	cpy /= p_b;
	return cpy;
}

Vec4 operator/(double p_a, const Vec4& p_b)
{
	return p_b / p_a;
}

double Vec4::dot(const Vec4& p_b) const
{
	return m_x * p_b.m_x + m_y * p_b.m_y + m_z * p_b.m_z;
}

double Vec4::norm()
{
	return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

void Vec4::normalize()
{
	*this /= m_w;
}

void Vec4::print(std::string p_name) const
{
	std::cout << p_name << ": " << toString() << std::endl;
}

std::string Vec4::toString() const
{
	return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ", " + std::to_string(m_w) + ")";
}

double Vec4::getX() const
{
	return m_x;
}

double Vec4::getY() const
{
	return m_y;
}

double Vec4::getZ() const
{
	return m_z;
}

double Vec4::getNorm() const
{
	return m_w;
}

Vec4N Vec4::getNormalized()
{
	Vec4 cpy = Vec4(*this);
	cpy.normalize();
	return Vec4N(cpy);
}

// Normalized Vector

Vec4N::Vec4N() : 
Vec4()
{
}

Vec4N::Vec4N(double p_x, double p_y, double p_z) :
Vec4(p_x, p_y, p_z)
{
#ifdef _DEBUG
	check();
#endif
}

Vec4N::Vec4N(const Vec4& p_cpy) :
Vec4(p_cpy)
{
#ifdef _DEBUG
	check();
#endif
}


Vec4N::Vec4N(const Vec4N& p_cpy) :
Vec4(p_cpy)
{
#ifdef _DEBUG
	check();
#endif
}

Vec4N::~Vec4N()
{
}

void Vec4N::check()
{
	if (m_w < 1 - EPSILON || m_w > 1 + EPSILON)
		throw Exception("Vec4N must be a normalized vector");
}
