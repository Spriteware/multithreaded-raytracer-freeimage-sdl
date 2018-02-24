#include "pyramid.h"

Pyramid::Pyramid()
{
}

Pyramid::Pyramid(const Vec4& p_p1, const Vec4& p_p2, const Vec4& p_p3, const Vec4& p_p4) :
Object(p_p1 + (p_p2 - p_p1) / 2.0 + (p_p3 - p_p1) / 2.0 + (p_p4 - p_p1) / 2.0) // m_pos will be the pyramid's center
{
	m_p1 = p_p1;
	m_p2 = p_p2;
	m_p3 = p_p3;
	m_p4 = p_p4;

	m_front = Triangle(p_p1, p_p2, p_p3);
	m_left = Triangle(p_p1, p_p3, p_p4);
	m_right = Triangle(p_p1, p_p2, p_p4);
	m_base = Triangle(p_p2, p_p4, p_p3);
}

Pyramid::~Pyramid()
{
}

bool Pyramid::intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2)
{
	if (m_front.intersect(p_origin, p_direction, p_p1, p_p2))
		return true;

	if (m_left.intersect(p_origin, p_direction, p_p1, p_p2))
		return true;

	if (m_right.intersect(p_origin, p_direction, p_p1, p_p2))
		return true;

	if (m_base.intersect(p_origin, p_direction, p_p1, p_p2))
		return true;

	return false;
}

bool Pyramid::update(Vec4* p_velocity)
{
	return false;
}

Vec4N Pyramid::getNormalAt(const Vec4& p_pt)
{
	return (p_pt - m_pos).getNormalized();
}
