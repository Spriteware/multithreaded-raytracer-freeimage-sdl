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
					RGBQUAD color = obj->getColor();
					Vec4 pt = Vec4(p1); // cpy
					double distance = (pt - m_camera.getPos()).getNorm();

					/*if (i == (int)img_half_width - 10 && j == (int)img_half_height)
					{
						std::cout << "k: " << k << "  " << i << ";" << j << std::endl;
						//std::cout << "pixels here r: " << (int)m_pixels[i][j].rgbRed << " g: " << (int)m_pixels[i][j].rgbGreen << " b: " << (int)m_pixels[i][j].rgbBlue << std::endl;
						obj->getPos().print("obj_pos");
						std::cout << "norm: " << pt.getNorm() << std::endl;
						std::cout << std::endl;
					}*/
					
					// Keep going only if it's the nearest point
					if (distance >= lowest_distance)
						continue;
					lowest_distance = distance;

					Vec4 light_vec = light.getPos() - pt;
					Vec4N light_ray = light_vec.getNormalized();
					bool lightened = true;

					// Fetch if there is no intersection between object and light (Diffuse light)
					for (n = 0; n < n_objects && lightened == true; ++n)
					{
						if (n == k) // skip current object
							continue;

						// TODO check that the light is not between the object and the detect one
						if (m_objects[n]->intersect(pt, light_ray, &p1, &p2))
							lightened = false;
					}
					
					float diffuse = 0.f, specular = 0.f;

					if (lightened)
					{
						Vec4N normal = obj->getNormalAt(pt);
						float att = 1.f / light_ray.getNorm(); // attenuation, not sure it's really usefull (TODO)

						// Compute diffuse light
						diffuse = normal.dot(light_ray);
						diffuse = att * DIFFUSE_LIGHT_FACTOR * diffuse > 0 ? diffuse : 0;

						// Compute specular light
						Vec4N median = (ray * -1 + light_ray).getNormalized();
						specular = std::pow(normal.dot(median), SPECULAR_SHININESS);
						specular = att * SPECULAR_LIGHT_FACTOR * specular > 0 ? specular : 0;
					}

					float lux = AMBIENT_LIGHT_FACTOR + diffuse;
					lux = lux > 1.0f ? 1.0f : lux;

					int r = color.rgbRed * lux + 255 * specular;
					int g = color.rgbGreen * lux + 255 * specular;
					int b = color.rgbBlue * lux + 255 * specular;

					// Combine Ambient and Diffuse light
					m_pixels[i][j].rgbRed = r > 255 ? 255 : r;
					m_pixels[i][j].rgbGreen = g > 255 ? 255 : g;
					m_pixels[i][j].rgbBlue = b > 255 ? 255 : b;
				}
			}

			if (i == 0 && j == 0)
				std::cout << "one pass: all good. " << std::endl;
		}
	}

	return true;
}

bool Scene::save()
{
	std::cout << "saving..." << std::endl;

	FIBITMAP* img = FreeImage_Allocate(IMG_WIDTH, IMG_HEIGHT, 24);
	RGBQUAD pixel;

	for (int i = 0; i < IMG_WIDTH; i++)
	{
		for (int j = 0; j < IMG_HEIGHT; j++)
		{
			pixel = m_pixels[i][j];
			FreeImage_SetPixelColor(img, i, j, &pixel);
		}
	}

	FreeImage_Save(FIF_PNG, img, "../saved.png");

	return true;
}