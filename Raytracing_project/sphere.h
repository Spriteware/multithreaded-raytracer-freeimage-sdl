#pragma once
#include "object.h"

class Sphere : public Object
{
protected:
	float m_radius;

public:
	Sphere();
	Sphere(const Vec4& p_pos, float p_radius);
	Sphere(const Object& p_cpy);
	~Sphere();

	float getRadius();
	bool intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2) override;
	Vec4N getNormalAt(const Vec4& p_pt) override;
};
