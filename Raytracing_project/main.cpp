#include <iostream>
#include "scene.h"
#include "sphere.h"
#include "plane.h"

int main(int argc, char *argv[])
{
	Scene* scene = new Scene(); // for memory purpose, we register it in the stack
	float focale = 3.f;
	Camera cam(Vec4(0, 2, -10), Vec4N(0, 0, 1), focale);

	scene->setCamera(cam);
	scene->addLight(Light(Vec4(0, 10, -5)));

	scene->addObject(new Plane(Vec4(0, -3, 0), Vec4(0.01, 0.5, 0).getNormalized()), Colors::WHITE);
	scene->addObject(new Sphere(Vec4(-2, 0, -2), 1), Colors::BLUE);
	scene->addObject(new Sphere(Vec4(-1.5, 0, 1), 1), Colors::WHITE);
	scene->addObject(new Sphere(Vec4(5, 0, 0), 1), Colors::GREEN);
	scene->addObject(new Sphere(Vec4(1, 4, 0), 2), Colors::RED);
	
	if (scene->render()) {
		std::cout << "scene correctly rendered" << std::endl;
		scene->save();
	}

	system("pause");

	return EXIT_SUCCESS;
}
