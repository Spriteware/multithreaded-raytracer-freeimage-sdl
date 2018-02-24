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
#define IMG_WIDTH 550
#define IMG_HEIGHT 400

class Scene
{
protected:
	Camera* m_camera;
	std::vector<Light*> m_lights;
	std::vector<Object*> m_objects;
	RGBQUAD m_pixels[IMG_WIDTH][IMG_HEIGHT];

public:
	Scene();
	~Scene();

	void setCamera(Camera* p_camera);
	void addLight(Light* p_light);
	void addObject(Object* p_object, Colors p_color);

	bool render(Animated& p_anim);
	bool renderObject(Object* p_obj, const Vec4& p_ray, double *p_lowest_distance, const unsigned int p_i, const unsigned int p_j);
	bool save(std::string p_filename);

	FIBITMAP* getFitbitMap();
};