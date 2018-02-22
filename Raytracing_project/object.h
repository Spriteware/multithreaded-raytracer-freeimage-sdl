#pragma once
#include <FreeImage.h>
#include "vec4.h"

enum Colors {
	WHITE, BLUE, RED, GREEN
};

class Object
{
protected:
	Vec4 m_pos;
	RGBQUAD m_color;

public:
	Object();
	Object(const Vec4& p_pos);
	Object(const Vec4& p_pos, const RGBQUAD& p_color);
	Object(const Vec4& p_pos, Colors p_color);
	Object(const Object& p_cpy);
	~Object();
	
	virtual bool intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2) = 0;
	RGBQUAD rgb(const char r, const char g, const char b) const;

	virtual Vec4N getNormalAt(const Vec4& p_pt) = 0;
	Vec4 getPos() const;
	void setPos(const Vec4& p_pos);
	RGBQUAD getColor();
	void setColor(Colors p_color);
	void setColor(const RGBQUAD& p_color);
};
