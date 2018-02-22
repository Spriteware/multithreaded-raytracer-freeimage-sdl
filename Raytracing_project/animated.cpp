#include "animated.h"

Animated::Animated()
{
	m_velocity = Vec4(0, 0, 0);
	m_gravity = Vec4(0, GRAVITY, 0);
}

Animated::Animated(Object * p_obj)
{
	m_obj = p_obj;
}

Animated::~Animated()
{
}

void Animated::update()
{
	// Simple "gravity function"

	Vec4 pos = m_obj->getPos();
	Vec4 next_pos = pos + m_velocity;
	double y = pos.getY();
	double epsilon = 0.001f;

	if (y <= 0 && m_velocity.getNorm() < epsilon) {
		m_velocity *= 0.7f; // Attenuate speed
		next_pos = Vec4(next_pos.getX(), epsilon, next_pos.getY());
	}
	else if (y <= 0) {
		m_velocity *= -0.8; // bounce and lose speed
		next_pos = Vec4(next_pos.getX(), epsilon, next_pos.getY());
	}

	m_obj->setPos(next_pos);
}

Vec4 Animated::getVelocity() const 
{
	return m_velocity;
}

void Animated::setVelocity(const Vec4& p_velocity)
{
	m_velocity = p_velocity;
}