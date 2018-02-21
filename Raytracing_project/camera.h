#include "vec4.h"

#define PI 3.14159265359

class Camera
{
protected:
	Vec4 m_pos;
	Vec4N m_direction;
	Vec4 m_rayBase;
	double m_focale;
	int m_hfov;		// horizontal field of view
	int m_vfov;		// horizontal field of view

	int m_screenWidth;
	int m_screenHeight;
	double m_screenMidWidth;
	double m_screenMidHeight;
	double m_screenHPas;
	double m_screenVPas;

	bool m_ready = false; // if projection is ready

public:
	Camera();
	Camera(const Vec4& p_pos, const Vec4N& p_direction, float p_focale);
	~Camera();

	void computeProjection(int p_width, int p_height);

	Vec4N getRayForPixel(int p_x, int p_y);
	Vec4 getPos();
	Vec4N getDirection();
	double getFocale();
	void setFieldOfView(int p_horizontal, int p_vertical);
};
