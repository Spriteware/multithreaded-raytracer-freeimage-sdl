#include "vec4.h"

#define PI 3.14159265359

class Camera
{
protected:
	Vec4 m_pos;
	Vec4 m_direction;
	float m_focale;

public:
	Camera();
	Camera(const Vec4& p_pos, const Vec4& p_direction, float p_focale);
	~Camera();

	Vec4 getPos();
	Vec4 getDirection();
	float getFocale();
};
