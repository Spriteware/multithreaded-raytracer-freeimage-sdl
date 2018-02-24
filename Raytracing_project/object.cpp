#include "object.h"

Object::Object()
{
	m_isAnimated = false;
}

Object::Object(const Vec4& p_pos)
{
	m_pos = p_pos;
	m_color = rgb(255, 255, 255);
	m_isAnimated = false;
}

Object::Object(const Vec4& p_pos, const RGBQUAD& p_color)
{
	m_pos = p_pos;
	m_color = p_color;
	m_isAnimated = false;
}

Object::Object(const Vec4& p_pos, Colors p_color)
{
	m_pos = p_pos;
	setColor(p_color);
	m_isAnimated = false;
}

Object::Object(const Object& p_cpy)
{
	m_pos = p_cpy.m_pos;
	m_color = p_cpy.m_color;
}

Object::~Object()
{
}

RGBQUAD Object::rgb(const char r, const char g, const char b) const
{
	RGBQUAD color;
	color.rgbRed = r;
	color.rgbGreen = g;
	color.rgbBlue = b;

	return color;
}

Vec4 Object::getPos() const 
{
	return m_pos;
}

void Object::setPos(const Vec4& p_pos)
{
	m_pos = p_pos;
}

RGBQUAD Object::getColor()
{
	return m_color;
}

void Object::setColor(Colors p_color)
{
	RGBQUAD color;

	if (p_color == Colors::RED)
		color = rgb(231, 76, 60);
	else if (p_color == Colors::GREEN)
		color = rgb(46, 204, 113);
	else if (p_color == Colors::BLUE)
		color = rgb(52, 152, 219);
	else if (p_color == Colors::YELLOW)
		color = rgb(241, 196, 15);
	else
		color = rgb(255, 255, 255);

	m_color = color;
}

void Object::setColor(const RGBQUAD& p_color)
{
	m_color = p_color;
}

void Object::setAnimated(bool p_value)
{
	m_isAnimated = p_value;
}

bool Object::isAnimated() const
{
	return m_isAnimated;
}