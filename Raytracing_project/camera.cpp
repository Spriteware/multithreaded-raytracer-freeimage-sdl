#include "camera.h"

Camera::Camera()
{
}

Camera::Camera(const Vec4& p_pos, const Vec4N& p_direction, float p_focale)
{
	m_ready = false;
	m_pos = p_pos;
	m_direction = p_direction;
	m_focale = p_focale;
	m_hfov = 90;
	m_vfov = 90;

	m_direction.normalize();
}

Camera::~Camera()
{
}

void Camera::computeProjection(int p_width, int p_height)
{
	// compute the projection screen
	double hmid_projec = std::tan(m_hfov / 2.0 * PI / 180.0) * m_focale;
	double vmid_projec = std::tan(m_vfov / 2.0 * PI / 180.0) * m_focale;
	double hprojec = hmid_projec * 2.0;
	double vprojec = vmid_projec * 2.0;

	m_screenWidth = p_width;
	m_screenHeight = p_height;
	m_screenMidWidth = p_width / 2.0;
	m_screenMidHeight = p_height / 2.0;
	m_screenHPas = hprojec / (double)p_width;
	m_screenVPas = vprojec / (double)p_height;

	m_rayBase = m_direction * m_focale;
	m_ready = true;
}

Vec4N Camera::getRayForPixel(int p_x, int p_y)
{
#ifdef _DEBUG
	if (!m_ready)
		throw new Exception("You need to compute the projection before doing anything else with the camera.");
#endif

	// TODO rotate in the camera's coords! /!\  
	double x = (p_x - m_screenMidWidth) * m_screenHPas;
	double y = (p_y - m_screenMidHeight) * m_screenVPas;
	return (m_rayBase + Vec4(x, y, 0)).getNormalized();
}

Vec4 Camera::getPos()
{
	return m_pos;
}

Vec4N Camera::getDirection()
{
	return m_direction;
}

float Camera::getFocale()
{
	return m_focale;
}

void Camera::setFieldOfView(int p_horizontal, int p_vertical)
{
	m_hfov = p_horizontal;
	m_vfov = p_vertical;
}