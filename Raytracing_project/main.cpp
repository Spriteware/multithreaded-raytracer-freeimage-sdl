#include <iostream>
#include <chrono>
#include <thread>
#include "sdl.h"
#include "scene.h"
#include "sphere.h"
#include "plane.h"

#define NB_THREADS 4
#define FRAMES 50	// 2secs at 24fps

int main(int argc, char* argv[])
{
	// Multithreading is used to split the image in various part 
	//std::thread threads[NB_THREADS];
	SDL_Texture* rendered_imgs[FRAMES];

	SDL_Window* sdl_window = get_sdl_window(IMG_WIDTH, IMG_HEIGHT);
	SDL_Renderer* sdl_renderer = create_renderer(sdl_window);
	
	// Animated object here
	Sphere *s = new Sphere(Vec4(5, 4, 0), 1);
	Animated anim(s);

	for (int i = 0; i < FRAMES; i++)
	{
		// For memory purpose, we register everything in the stack
		Scene* scene = new Scene();
		Camera cam(Vec4(0, 2, -10), Vec4N(0, 0, 1), 3.f); // 3.f is the focale

		scene->setCamera(cam);
		scene->addLight(Light(Vec4(0, 10, -5)));

		scene->addObject(new Plane(Vec4(0, -3, 0), Vec4(0.01, 0.5, 0).getNormalized()), Colors::WHITE);
		scene->addObject(new Sphere(Vec4(-2, 0, -2), 1), Colors::BLUE);
		scene->addObject(new Sphere(Vec4(-1.5, 0, 1), 1), Colors::WHITE);
		scene->addObject(new Sphere(Vec4(1, 4, 0), 2), Colors::RED);
		scene->addObject(s, Colors::GREEN);

		// Render the final scene
		anim.update();
		scene->render(anim);
		std::cout << "scene #" << i << " correctly rendered" << std::endl;

		// Create and register texture
		FIBITMAP* img = scene->getFitbitMap();
		SDL_Surface* sdl_surface = get_sdl_surface(img, false);
		SDL_Texture* sdl_texture = get_sdl_texture(sdl_surface, sdl_renderer);
		rendered_imgs[i] = sdl_texture;
	}
	
	std::cout << FRAMES << " frames have been rendered" << std::endl;

	//for (int i = 0; i < NB_THREADS; ++i)
	//	threads[i] = std::thread(&Scene::render, scene, int(IMG_WIDTH / 2), int(IMG_HEIGHT / 2));

	//std::cout << "all threads are working fine" << std::endl;

	//for (int i = 0; i < NB_THREADS; ++i)
	//	threads[i].join();

	// Start the animation
	int index = 0;
	while (event_loop() == false)
	{
		render_image(rendered_imgs[index], sdl_renderer);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));

		index = (index + 1) % FRAMES;
	}

	// Free SDL
	SDL_Quit();
	
	//scene->save();

	//std::cout << "exit by pressing a key...";
	//getchar();

	return EXIT_SUCCESS;
}
