#pragma once
#include <iostream>
#include <string>
#include "exception.h"

#define EPSILON 0.00001f

class Vec4N;

class Vec4
{
protected:
	double m_x;
	double m_y;
	double m_z;
	double m_w;
	
	double Vec4::norm();

public:
	Vec4();
	Vec4(double p_x, double p_y, double p_z);
	Vec4(const Vec4& p_cpy);
	~Vec4();

	bool isEqual(const Vec4& p_b) const;
	void operator+=(const Vec4& p_b);
	void operator-=(const Vec4& p_b);
	void operator*=(double p_b);
	void operator/=(double p_b);

	double dot(const Vec4& p_b) const;
	void normalize();
	void print(std::string p_name) const; // usefull for debug

	std::string toString() const;
	double getX() const;
	double getY() const;
	double getZ() const;
	double getNorm() const;
	Vec4N getNormalized();
};

// Normalized vector:
class Vec4N : public Vec4
{
private: 
	void check();

public:
	Vec4N();
	Vec4N(double p_x, double p_y, double p_z);
	Vec4N(const Vec4& p_cpy);
	Vec4N(const Vec4N& p_cpy);
	~Vec4N();
};

bool operator==(const Vec4& p_a, const Vec4& p_b);
bool operator!=(const Vec4& p_a, const Vec4& p_b);
Vec4 operator+(const Vec4& p_a, const Vec4& p_b);
Vec4 operator-(const Vec4& p_a, const Vec4& p_b);
Vec4 operator*(const Vec4& p_a, double p_b);
Vec4 operator*(double p_a, const Vec4& p_b);
Vec4 operator/(const Vec4& p_a, double p_b);
Vec4 operator/(double p_a, const Vec4& p_b);