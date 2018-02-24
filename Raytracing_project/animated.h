#pragma once
#include "object.h"

#define GRAVITY 0.1f
#define FRICTION 0.7f
#define BOUNCE 0.7f

class Animated
{
protected:
	int m_iterations;
	int m_state;
	Object* m_obj;
	Vec4 m_velocity;

public:
	Animated();
	Animated(int p_iterations, Object * p_obj, const Vec4& p_velocity);
	~Animated();

	Object* render();
	void update();
	Vec4 getVelocity() const;
	void setVelocity(const Vec4& p_velocity);
	Object* getObject() const;
	int getIterations() const;
};
