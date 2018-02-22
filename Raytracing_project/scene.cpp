#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include <thread>

Scene::Scene()
{
	m_test=  -1;
}

Scene::~Scene()
{
	// Free objects
	for (unsigned int i = 0; i < m_objects.size(); ++i)
		delete m_objects[i];
}

void Scene::setCamera(const Camera& p_camera)
{
	// Pre-compute the projection
	m_camera = p_camera;
	m_camera.computeProjection(IMG_WIDTH, IMG_HEIGHT);
}

void Scene::addLight(const Light& p_light)
{
	m_lights.push_back(p_light);
}

void Scene::addObject(Object* p_object, Colors p_color)
{
	m_objects.push_back(p_object);
	p_object->setColor(p_color);
}

bool Scene::render(Animated& p_anim, bool p_animate)
{
	std::cout << "rendering..." << std::endl;

	unsigned int i, j, k;
	unsigned int img_width = IMG_WIDTH;
	unsigned int img_height = IMG_HEIGHT;
	double img_half_width = IMG_WIDTH / 2.0;
	double img_half_height = IMG_HEIGHT / 2.0;
	double lowest_distance, numeric_max = std::numeric_limits<double>::max();

	Vec4N ray;
	Light light = m_lights[0];
	unsigned int n_objects = m_objects.size();
	unsigned int one_pass = 0;

	// Update animation if necessary
	if (p_animate)
		p_anim.update();

	// The following approach is based on inspired by
	// http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

	for (i = 0; i < img_width; ++i)
	{
		for (j = 0; j < img_height; ++j)
		{
			// Black by default (background)
			m_pixels[i][j].rgbRed = BYTE(255 * AMBIENT_LIGHT_FACTOR);
			m_pixels[i][j].rgbGreen = BYTE(255 * AMBIENT_LIGHT_FACTOR);
			m_pixels[i][j].rgbBlue = BYTE(255 * AMBIENT_LIGHT_FACTOR);

			ray = m_camera.getRayForPixel(i, j);
			lowest_distance = numeric_max;  // used for the z-index

			// Fetch for each object
			for (k = 0; k < n_objects; ++k)
			{
				Object* obj = m_objects[k];
				Vec4 p1, p2;

				// Test for intersection with ray and save it in p1 and p2. p1 is the nearest
				if (obj->intersect(m_camera.getPos(), ray, &p1, &p2))
				{
					Vec4 pt = Vec4(p1); // copy
					double distance = (pt - m_camera.getPos()).getNorm();

					// Keep going only if it's the nearest point
					if (distance >= lowest_distance)
						continue;
					lowest_distance = distance;

					// Get the colors enlighted by the right light
					int r, g, b;
					light.enlight(ray, obj, pt, m_objects, &r, &g, &b);

					// Apply colors on pixels
					m_pixels[i][j].rgbRed = BYTE(r > 255 ? 255 : r);
					m_pixels[i][j].rgbGreen = BYTE(g > 255 ? 255 : g);
					m_pixels[i][j].rgbBlue = BYTE(b > 255 ? 255 : b);

#ifdef _DEBUG
					one_pass = one_pass < 1 ? 1 : one_pass; // debug. cf next info
#endif
				}
			}

#ifdef _DEBUG
			// Some bugs can not appears on Release, but Debug mode is slow, so you can check one pass of the algorithm thanks to the next line
			if (one_pass == 1) {
				std::cout << "one pass: all good. " << std::endl;
				one_pass++;
			}
#endif
		}
	}

	return true;
}

bool Scene::save()
{
	std::cout << "saving..." << std::endl;

	FIBITMAP* img = getFitbitMap();
	FreeImage_Save(FIF_PNG, img, "../saved.png");
	FreeImage_Unload(img);
	return true;
}


FIBITMAP* Scene::getFitbitMap()
{
	FIBITMAP* img = FreeImage_Allocate(IMG_WIDTH, IMG_HEIGHT, 24);

	// Go over all the pixels 
	for (int i = 0; i < IMG_WIDTH; i++)
		for (int j = 0; j < IMG_HEIGHT; j++)
			FreeImage_SetPixelColor(img, i, j, &(m_pixels[i][j]));

	return img;
}