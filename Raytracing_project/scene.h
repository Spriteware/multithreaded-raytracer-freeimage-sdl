#pragma once
#include <FreeImage.h>
#include <iostream>
#include <vector>
#include <limits>

#include "animated.h"
#include "camera.h"
#include "object.h"
#include "light.h"

// todo: to compute that with the camera
#define IMG_WIDTH 1100
#define IMG_HEIGHT 800

class Scene
{
protected:
	Camera m_camera;
	std::vector<Light> m_lights;
	std::vector<Object*> m_objects;
	RGBQUAD m_pixels[IMG_WIDTH][IMG_HEIGHT];
	float m_test;

public:
	Scene();
	~Scene();

	void setCamera(const Camera& p_camera);
	void addLight(const Light& p_light);
	void addObject(Object* p_object, Colors p_color);

	bool render(Animated& p_anim);
	bool save();

	FIBITMAP* getFitbitMap();
};