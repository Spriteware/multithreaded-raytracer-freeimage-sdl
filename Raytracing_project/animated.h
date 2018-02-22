#pragma once
#include "object.h"

#define GRAVITY 0.1

class Animated
{
protected:
	Object* m_obj;
	Vec4 m_velocity;
	Vec4 m_gravity;

public:
	Animated();
	Animated(Object * p_obj);
	~Animated();

	void update();
	Vec4 getVelocity() const;
	void setVelocity(const Vec4& p_velocity);
};
