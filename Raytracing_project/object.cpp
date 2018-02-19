#include "object.h"

Object::Object()
{
}

Object::Object(const Vec4& p_pos)
{
	m_pos = p_pos;
	m_color = rgb(255, 255, 255);
}

Object::Object(const Vec4& p_pos, const RGBQUAD& p_color)
{
	m_pos = p_pos;
	m_color = p_color;
}

Object::Object(const Vec4& p_pos, Colors p_color)
{
	m_pos = p_pos;
	setColor(p_color);
}

Object::Object(const Object& p_cpy)
{
	m_pos = p_cpy.m_pos;
	m_color = p_cpy.m_color;
}

Object::~Object()
{
}

RGBQUAD Object::rgb(char r, char g, char b) const
{
	RGBQUAD color;
	color.rgbRed = r;
	color.rgbGreen = g;
	color.rgbBlue = b;

	return color;
}

Vec4 Object::getPos()
{
	return m_pos;
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
	else
		color = rgb(255, 255, 255);

	m_color = color;
}

void Object::setColor(const RGBQUAD& p_color)
{
	m_color = p_color;
}

