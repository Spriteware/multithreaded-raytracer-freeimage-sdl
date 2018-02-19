#pragma once
#include "object.h"

class Cube : public Object
{
protected:
	float m_width;
	float m_height;
	float m_depth;

public:
	Cube();
	Cube(const Vec4& p_pos, float p_width, float p_height, float p_depth);
	~Cube();
};
