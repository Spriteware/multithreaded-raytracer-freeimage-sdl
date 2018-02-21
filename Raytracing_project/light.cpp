#include "light.h"

Light::Light()
{
}

Light::Light(const Vec4& p_pos)
{
	m_pos = p_pos;
}

Light::~Light()
{
}

void Light::enlight(const Vec4& p_camRay, Object* p_obj, const Vec4& p_pt, const std::vector<Object*>& p_objects, int *r, int *g, int *b)
{
	Vec4 light_vec = m_pos - p_pt;
	Vec4N light_ray = light_vec.getNormalized();
	double light_distance = light_vec.getNorm();
	bool lightened = true;
	unsigned int n, n_objects = p_objects.size();
	Vec4 p1, p2;

	// Fetch if there is no intersection between object and light (Diffuse light)
	for (n = 0; n < n_objects; ++n)
	{
		if (p_objects[n] == p_obj) // skip current object
			continue;

		// Verify that the pt is between, stop light computing if it is 
		if (p_objects[n]->intersect(p_pt, light_ray, &p1, &p2)) {
			if ((p1 - p_pt).getNorm() >= light_distance)
				continue;

			lightened = false;
			break;
		}
	}

	double diffuse = 0.f, specular = 0.f;

	if (lightened)
	{
		Vec4N normal = p_obj->getNormalAt(p_pt);
		double att = 1.f / light_ray.getNorm(); // attenuation, not sure it's really usefull (TODO)

		// Compute diffuse light
		diffuse = normal.dot(light_ray);
		diffuse = att * DIFFUSE_LIGHT_FACTOR * diffuse > 0 ? diffuse : 0.f;

		// Compute specular light
		Vec4N median = (p_camRay * -1 + light_ray).getNormalized();
		specular = std::pow(normal.dot(median), SPECULAR_SHININESS);
		specular = att * SPECULAR_LIGHT_FACTOR * specular > 0 ? specular : 0.f;
	}

	RGBQUAD color = p_obj->getColor();
	float lux = float(AMBIENT_LIGHT_FACTOR + diffuse);
	lux = lux > 1.0f ? 1.0f : lux;

	*r = int(color.rgbRed * lux + 255 * specular);
	*g = int(color.rgbGreen * lux + 255 * specular);
	*b = int(color.rgbBlue * lux + 255 * specular);
}

Vec4 Light::getPos()
{
	return m_pos;
}

