#pragma once
#include "object.h"

class Plane : public Object
{
protected:
	Vec4 m_normal;

public:
	Plane();
	Plane(const Vec4& p_pos, const Vec4N& p_normal);
	Plane(const Object& p_cpy);
	~Plane();

	Vec4 getNormal();
	bool intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2) override;
	Vec4N getNormalAt(const Vec4& p_pt) override;
};
