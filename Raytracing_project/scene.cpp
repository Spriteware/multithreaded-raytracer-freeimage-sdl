#include "scene.h"
#include "sphere.h"
#include "plane.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	// Free objects
	for (unsigned int i = 0; i < m_objects.size(); ++i)
	{
		delete m_objects[i];
		m_objects[i] = NULL;
	}
}

void Scene::setCamera(const Camera& p_camera)
{
	m_camera = p_camera;
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

bool Scene::render()
{
	std::cout << "rendering..." << std::endl;

	unsigned int i, j, k, n;
	double x, y, lowest_distance;

	double img_width = IMG_WIDTH;
	double img_height = IMG_HEIGHT;
	double img_half_width = IMG_WIDTH / 2.0;
	double img_half_height = IMG_HEIGHT / 2.0;

	Vec4N ray;
	Light light = m_lights[0];
	int n_objects = m_objects.size();
	int one_pass = 0;
	
	// Pre-compute the projection
	m_camera.computeProjection(img_width, img_height);

	// The following approach is based on inspired by
	// http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

	for (i = 0; i < img_width; ++i)
	{
		for (j = 0; j < img_height; ++j)
		{
			// Black by default (background)
			m_pixels[i][j].rgbRed = 255 * AMBIENT_LIGHT_FACTOR;
			m_pixels[i][j].rgbGreen = 255 * AMBIENT_LIGHT_FACTOR;
			m_pixels[i][j].rgbBlue = 255 * AMBIENT_LIGHT_FACTOR;

			ray = m_camera.getRayForPixel(i, j);
			lowest_distance = std::numeric_limits<double>::max();  // used for the z-index

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
					m_pixels[i][j].rgbRed = r > 255 ? 255 : r;
					m_pixels[i][j].rgbGreen = g > 255 ? 255 : g;
					m_pixels[i][j].rgbBlue = b > 255 ? 255 : b;

					one_pass = 1; // debug. cf next info
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

	FIBITMAP* img = FreeImage_Allocate(IMG_WIDTH, IMG_HEIGHT, 24);
	RGBQUAD pixel;

	// Go over all the pixels 
	for (int i = 0; i < IMG_WIDTH; i++)
		for (int j = 0; j < IMG_HEIGHT; j++)
			FreeImage_SetPixelColor(img, i, j, &(m_pixels[i][j]));

	FreeImage_Save(FIF_PNG, img, "../saved.png");

	return true;
}