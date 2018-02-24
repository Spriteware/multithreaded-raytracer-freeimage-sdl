#pragma once
#include "triangle.h"

class Pyramid : public Object
{
protected:
	Vec4 m_p1;
	Vec4 m_p2;
	Vec4 m_p3;
	Vec4 m_p4;
	Triangle m_front;
	Triangle m_left;
	Triangle m_right;
	Triangle m_base;

public:
	Pyramid();
	Pyramid(const Vec4& p_p1, const Vec4& p_p2, const Vec4& p_p3, const Vec4& p_p4);
	Pyramid(const Object& p_cpy);
	~Pyramid();

	bool intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2) override;
	bool update(Vec4* p_velocity) override;
	Vec4N getNormalAt(const Vec4& p_pt) override;
};
