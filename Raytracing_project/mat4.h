#pragma once
#include "vec4.h"

class Mat4
{
protected:
	Vec4 m_x;
	Vec4 m_y;
	Vec4 m_z;
	Vec4 m_w;

public:
	Mat4();
	Mat4(const Vec4& p_x, const Vec4& p_y, const Vec4& p_z);
	Mat4(const Mat4& p_cpy);
	~Mat4();

	Vec4 getX() const;
	Vec4 getY() const;
	Vec4 getZ() const;
};

Vec4 operator*(const Mat4& p_a, const Vec4& p_b);