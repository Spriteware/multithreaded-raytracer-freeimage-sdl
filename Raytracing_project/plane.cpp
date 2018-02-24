#include "plane.h"

Plane::Plane()
{
}

Plane::Plane(const Vec4& p_pos, const Vec4N& p_normal) :
Object(p_pos)
{
	m_normal = p_normal;
}

Plane::~Plane()
{
}

Vec4 Plane::getNormal()
{
	return m_normal;
}

bool Plane::intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2)
{
	double denom = m_normal.dot(p_direction);
	if (denom > -EPSILON && denom < EPSILON)
		return false;

	double t = (m_pos - p_origin).dot(m_normal) / denom;
	if (t < 0)
		return false;

	*p_p1 = p_origin + p_direction * t;
	return true;
}

bool Plane::update(Vec4* p_velocity)
{
	return false;
}

Vec4N Plane::getNormalAt(const Vec4& p_pt)
{
	return m_normal;
}
