#pragma once
#include "vec4.h"

#define AMBIENT_LIGHT_FACTOR 0.1
#define DIFFUSE_LIGHT_FACTOR 0.9
#define SPECULAR_LIGHT_FACTOR 0.2
#define SPECULAR_SHININESS 100.0f // between 0.0f and 100.0f

class Light
{
protected:
	Vec4 m_pos;

public:
	Light();
	Light(const Vec4& p_pos);
	~Light();

	Vec4 getPos();
};
