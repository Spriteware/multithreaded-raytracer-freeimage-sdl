#include "sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(const Vec4& p_pos, float p_radius) :
Object(p_pos)
{
	m_radius = p_radius;
}

Sphere::~Sphere()
{
}

float Sphere::getRadius()
{
	return m_radius;
}

bool Sphere::intersect(const Vec4& p_origin, const Vec4N& p_direction, Vec4* p_p1, Vec4* p_p2)
{
	/*	
		The following approach is based on inspired by
		http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html and 
		https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/minimal-ray-tracer-rendering-spheres
	*/

	// Solve for tc
	Vec4 L = m_pos - p_origin;
	double l = L.getNorm();
	double tc = L.dot(p_direction);

	// No intersection if it's behind the object, we only test in the right direction
	if (tc < 0.f) 
		return false;

	//double d2 = std::abs(tc*tc - l*l);
	double d2 = L.dot(L) - tc*tc; // L.dot == norm(L)²
	double radius2 = m_radius * m_radius;

	if (d2 > radius2) // no intersection
		return false;

	// Solve for t1c
	double t1c = std::sqrt(radius2 - d2);

	// Solve for intersection points
	double t1 = tc - t1c;
	double t2 = tc + t1c;
	Vec4 p1 = p_direction * t1;
	Vec4 p2 = p_direction * t2;

	*p_p1 = p_origin + p1;
	*p_p2 = p_origin + p2;

	// Put p_p1 as the nearest
	if (p1.getNorm() > p2.getNorm()) {
		*p_p1 = p_origin + p2;
		*p_p2 = p_origin + p1;
	}

	return true;
}

bool Sphere::update(Vec4* p_velocity)
{
	// Simple "gravity function". 
	Vec4 next_pos = m_pos + *p_velocity;
	Vec4 gravity = Vec4(0, GRAVITY, 0);

	double y = m_pos.getY();
	double epsilon = 0.001f;
	double y_limit = m_radius;
	double vx = p_velocity->getX();
	double vy = p_velocity->getY();
	double vz = p_velocity->getZ();

	if (y <= y_limit && p_velocity->getNorm() < epsilon) {
		*p_velocity *= FRICTION; // Attenuate speed
		next_pos = Vec4(next_pos.getX(), y_limit + epsilon, next_pos.getZ());
	}
	else if (y <= y_limit) {
		*p_velocity = Vec4(vx * FRICTION, vy * -BOUNCE, vz * BOUNCE); // bounce and lose speed
		next_pos = Vec4(next_pos.getX(), y_limit + epsilon, next_pos.getZ());
	}
	else {
		*p_velocity -= gravity;
	}

	m_pos = next_pos;
	return true;
}

Vec4N Sphere::getNormalAt(const Vec4& p_pt)
{
	return (p_pt - m_pos).getNormalized();
}
