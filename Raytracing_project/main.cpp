#include <iostream>
#include <thread>
#include "sdl.h"
#include "scene.h"
#include "sphere.h"
#include "plane.h"

#define NB_THREADS 4

int main(int argc, char* argv[])
{
	// Multithreading is used to split the image in various part 
	//std::thread threads[NB_THREADS];
	
	// For memory purpose, we register everything in the stack
	Scene* scene = new Scene(); 
	Camera cam(Vec4(0, 2, -10), Vec4N(0, 0, 1), 3.f); // 3.f is the focale

	scene->setCamera(cam);
	scene->addLight(Light(Vec4(0, 10, -5)));

	scene->addObject(new Plane(Vec4(0, -3, 0), Vec4(0.01, 0.5, 0).getNormalized()), Colors::WHITE);
	scene->addObject(new Sphere(Vec4(-2, 0, -2), 1), Colors::BLUE);
	scene->addObject(new Sphere(Vec4(-1.5, 0, 1), 1), Colors::WHITE);
	scene->addObject(new Sphere(Vec4(1, 4, 0), 2), Colors::RED);

	// Animated object here
	Sphere *s = new Sphere(Vec4(5, 0, 0), 1);
	scene->addObject(s, Colors::GREEN);

	
	//for (int i = 0; i < NB_THREADS; ++i)
	//	threads[i] = std::thread(&Scene::render, scene, int(IMG_WIDTH / 2), int(IMG_HEIGHT / 2));

	//std::cout << "all threads are working fine" << std::endl;

	//for (int i = 0; i < NB_THREADS; ++i)
	//	threads[i].join();

	scene->render(Animated(s), false);
	std::cout << "scene correctly rendered" << std::endl;

	FIBITMAP* img = scene->getFitbitMap();
	SDL_Window* sdl_window = get_sdl_window(IMG_WIDTH, IMG_HEIGHT);
	SDL_Surface* sdl_surface = get_sdl_surface(img, false);

	render_image(sdl_window, sdl_surface);
	event_loop();

	FreeImage_Unload(img);
	SDL_FreeSurface(sdl_surface);
	SDL_Quit();
	
	//scene->save();

	//std::cout << "exit by pressing a key...";
	//getchar();

	return EXIT_SUCCESS;
}
