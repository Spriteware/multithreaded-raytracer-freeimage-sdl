#include "triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(const Vec4& p_p1, const Vec4& p_p2, const Vec4& p_p3) :
Object(p_p1 + (p_p2 - p_p1) / 2.0 + (p_p3 - p_p1) / 2.0) // m_pos will be the triangle's center
{
	m_p1 = p_p1;
	m_p2 = p_p2;
	m_p3 = p_p3;
}

Triangle::~Triangle()
{
}

bool Triangle::intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2)
{
	Vec4 p1p2 = m_p2 - m_p1;
	Vec4 p1p3 = m_p3 - m_p1;
	Vec4 pvec = p_direction * p1p3;
	double det = p1p2.dot(pvec);
#ifdef CULLING
	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < EPSILON) return false;
#else
	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < EPSILON)
		return false;
#endif
	float inv_det = 1 / det;

	Vec4 tvec = p_origin - m_p1;
	double u = tvec.dot(pvec) * inv_det;

	if (u < 0 || u > 1)
		return false;

	Vec4 qvec = tvec * (p1p2);
	double v = p_direction.dot(qvec) * inv_det;

	if (v < 0 || u + v > 1)
		return false;

	double t = p1p3.dot(qvec) * inv_det;
	Vec4 p = p_direction * t;
	*p_p1 = p_origin + p;
	*p_p2 = p_origin + p;
	
	return true;
}

bool Triangle::update(Vec4* p_velocity)
{
	return false;
}

Vec4N Triangle::getNormalAt(const Vec4& p_pt)
{
	Vec4 p1p2 = m_p2 - m_p1;
	Vec4 p1p3 = m_p3 - m_p1;
	return (p1p2 * p1p3).getNormalized() * -1;
}
