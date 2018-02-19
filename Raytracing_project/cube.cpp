#include "cube.h"

Cube::Cube()
{
}

Cube::Cube(const Vec4& p_pos, float p_width, float p_height, float p_depth) :
Object(p_pos)
{
	m_width = p_width;
	m_height = p_height;
	m_depth = p_depth;
}

Cube::~Cube()
{
}