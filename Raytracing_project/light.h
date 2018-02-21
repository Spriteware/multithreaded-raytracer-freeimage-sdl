#pragma once
#include <vector>
#include "object.h"

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

	void enlight(const Vec4& p_camRay, Object* p_obj, const Vec4& p_pt, const std::vector<Object*>& p_objects, int *r, int *g, int *b);
	Vec4 getPos();
};
