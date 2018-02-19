#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(const Vec4& p_pos, const Vec4& p_direction, float p_focale)
{
	m_pos = p_pos;
	m_direction = p_direction;
	m_focale = p_focale;

	m_direction.normalize();
}

Camera::~Camera()
{
}

Vec4 Camera::getPos()
{
	return m_pos;
}

Vec4 Camera::getDirection()
{
	return m_direction;
}

float Camera::getFocale()
{
	return m_focale;
}