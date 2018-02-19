#include "light.h"

Light::Light()
{
}

Light::Light(const Vec4& p_pos)
{
	m_pos = p_pos;
}

Light::~Light()
{
}

Vec4 Light::getPos()
{
	return m_pos;
}