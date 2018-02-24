#pragma once
#include "object.h"

class Triangle : public Object
{
protected:
	Vec4 m_p1;
	Vec4 m_p2;
	Vec4 m_p3;

public:
	Triangle();
	Triangle(const Vec4& p_p1, const Vec4& p_p2, const Vec4& p_p3);
	Triangle(const Object& p_cpy);
	~Triangle();

	bool intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2) override;
	bool update(Vec4* p_velocity) override;
	Vec4N getNormalAt(const Vec4& p_pt) override;
};
