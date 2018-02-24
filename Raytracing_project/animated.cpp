#include "animated.h"
#include "sphere.h"

Animated::Animated()
{
	m_iterations = 0;
	m_state = 0;
	m_velocity = Vec4(0, 0, 0);
}

Animated::Animated(int p_iterations, Object * p_obj, const Vec4& p_velocity) : Animated()
{
	m_iterations = p_iterations;
	m_velocity = p_velocity;
	m_obj = p_obj;
	m_obj->setAnimated(true);
}

Animated::~Animated()
{
}

Object* Animated::render()
{
	m_state = m_iterations;
	while (m_state--)
		update();
	return m_obj;
}

void Animated::update()
{
	m_obj->update(&m_velocity);
}

Vec4 Animated::getVelocity() const 
{
	return m_velocity;
}

void Animated::setVelocity(const Vec4& p_velocity)
{
	m_velocity = p_velocity;
}

Object* Animated::getObject() const
{
	return m_obj;
}