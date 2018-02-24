#include "mat4.h"

Mat4::Mat4()
{
}

Mat4::Mat4(const Vec4& p_x, const Vec4& p_y, const Vec4& p_z)
{
	m_x = p_x;
	m_y = p_y;
	m_z = p_z;
	m_w = Vec4(0, 0, 0, 1);
}

Mat4::Mat4(const Mat4& p_cpy)
{
	m_x = p_cpy.m_x;
	m_y = p_cpy.m_y;
	m_z = p_cpy.m_z;
	m_w = p_cpy.m_w;
}

Mat4::~Mat4()
{
}

Vec4 operator*(const Mat4& p_a, const Vec4& p_b)
{
	double x = p_a.getX().dot(p_b);
	double y = p_a.getY().dot(p_b);
	double z = p_a.getZ().dot(p_b);
	return Vec4(x, y, z);
}

Vec4 Mat4::getX() const
{
	return m_x;
}

Vec4 Mat4::getY() const
{
	return m_y;
}

Vec4 Mat4::getZ() const
{
	return m_z;
}