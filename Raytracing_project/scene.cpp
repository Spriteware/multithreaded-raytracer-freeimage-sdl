#include "scene.h"
#include "sphere.h"
#include "plane.h"
#include <thread>

Scene::Scene()
{
}

Scene::~Scene()
{
	// Free Objects
	for (unsigned int i = 0; i < m_objects.size(); ++i)
		delete m_objects[i];

	// Free Lights
	for (unsigned int i = 0; i < m_lights.size(); ++i)
		delete m_lights[i];
}

void Scene::setCamera(Camera* p_camera)
{
	// Pre-compute the projection
	m_camera = p_camera;
	m_camera->computeProjection(IMG_WIDTH, IMG_HEIGHT);
}

void Scene::addLight(Light* p_light)
{
	m_lights.push_back(p_light);
}

void Scene::addObject(Object* p_object, Colors p_color)
{
	m_objects.push_back(p_object);
	p_object->setColor(p_color);
}

//void Scene::addAnimatedObject(Animated* p_anim)
//{
//	m_animated.push_back(p_anim)
//}

bool Scene::render(Animated& p_anim)
{
	unsigned int i, j, k;
	unsigned int img_width = IMG_WIDTH;
	unsigned int img_height = IMG_HEIGHT;
	double img_half_width = IMG_WIDTH / 2.0;
	double img_half_height = IMG_HEIGHT / 2.0;
	double lowest_distance, numeric_max = std::numeric_limits<double>::max();

	// Compute the animation & add the object to the objects list
	Object* animated_obj = p_anim.render();
	m_objects.push_back(animated_obj);

	Vec4N ray;
	Light* light = m_lights[0]; // no various lights handling yet
	unsigned int n_objects = m_objects.size();
	unsigned int one_pass = 0;

	// The following approach is based on inspired by
	// http://kylehalladay.com/blog/tutorial/math/2013/12/24/Ray-Sphere-Intersection.html

	std::vector<RGBQUAD> matrix;

	for (i = 0; i < img_width; ++i)
	{
		for (j = 0; j < img_height; ++j)
		{
			// Black by default (background)
			m_pixels[i][j].rgbRed = BYTE(255 * AMBIENT_LIGHT_FACTOR);
			m_pixels[i][j].rgbGreen = BYTE(255 * AMBIENT_LIGHT_FACTOR);
			m_pixels[i][j].rgbBlue = BYTE(255 * AMBIENT_LIGHT_FACTOR);

			ray = m_camera->getRayForPixel(i, j);
			lowest_distance = numeric_max;  // used for the z-index

			// Render the animated object. We do it in first because it has great chances to be front
			////renderObject(animated_obj, ray, &lowest_distance, i, j);

			// Fetch for each object
			for (k = 0; k < n_objects; ++k)
				if (!renderObject(m_objects[k], ray, &lowest_distance, i, j))
					continue;

			matrix.push_back(m_pixels[i][j]);
		}
	}

	return true;
}

bool Scene::renderObject(Object* p_obj, const Vec4& p_ray, double *p_lowest_distance, const unsigned int p_i, const unsigned int p_j)
{
	Object* obj = p_obj;
	Light* light = m_lights[0];
	Vec4 p1, p2;

	// Test for intersection with ray and save it in p1 and p2. p1 is the nearest
	if (obj->intersect(m_camera->getPos(), p_ray, &p1, &p2))
	{
		Vec4 pt = Vec4(p1); // copy
		double distance = (pt - m_camera->getPos()).getNorm();

		// Keep going only if it's the nearest point
		if (distance >= *p_lowest_distance)
			return false;

		*p_lowest_distance = distance;

		// Get the colors enlighted by the right light
		int r, g, b;
		light->enlight(p_ray, obj, pt, m_objects, &r, &g, &b);

		// Apply colors on pixels
		m_pixels[p_i][p_j].rgbRed = BYTE(r > 255 ? 255 : r);
		m_pixels[p_i][p_j].rgbGreen = BYTE(g > 255 ? 255 : g);
		m_pixels[p_i][p_j].rgbBlue = BYTE(b > 255 ? 255 : b);

		return true;
	}

	return false;
}
bool Scene::save(const std::string p_filename)
{
	std::string file = "../saved/" + p_filename + ".png";
	std::cout << "saving in " << file << std::endl;

	FIBITMAP* img = getFitbitMap();
	FreeImage_Save(FIF_PNG, img, file.c_str());
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