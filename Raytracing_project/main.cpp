#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <list>
#include "sdl.h"
#include "scene.h"
#include "sphere.h"
#include "triangle.h"
#include "pyramid.h"
#include "plane.h"

#define _VERBOSE
//#define _SAVE_AS_FILE

#define FRAMES 140
// 2secs at 24fps
#define FPS 24

// We intialize everything in the global scope to reuse it for each thread.
SDL_Window* sdl_window = get_sdl_window(IMG_WIDTH, IMG_HEIGHT);
SDL_Renderer* sdl_renderer = create_renderer(sdl_window);

Camera* cam = new Camera(Vec4(0, 5, -10), Vec4N(0, 0, 1), 3.f); // 3.f is the focale
Plane* terrain = new Plane(Vec4(0, 0, 0), Vec4(0, 1, 0).getNormalized());
Sphere* blue = new Sphere(Vec4(-5, 4, -2), 1);
Sphere* white = new Sphere(Vec4(-3.5, 3, 1), 1);
Sphere* red = new Sphere(Vec4(2, 8, 3), 2);
//Triangle* t1 = new Triangle(Vec4(0, 3, 0), Vec4(-2, 0, 0), Vec4(2, 0, 0));
Pyramid* yellow = new Pyramid(Vec4(0, 4, 0), Vec4(-2, 1, 0), Vec4(2, 1, 0), Vec4(0, 1, 4));

int count = 0;

SDL_Texture* render(int p_id, int p_iteration)
{
	std::chrono::steady_clock::time_point end, begin = std::chrono::steady_clock::now();

	Scene* scene = new Scene();
	scene->setCamera(cam);
	scene->addObject(terrain, Colors::WHITE);
	scene->addObject(blue, Colors::BLUE);
	scene->addObject(red, Colors::RED);
	scene->addObject(yellow, Colors::YELLOW);
	
	//The following is the animated object, different from each frame
	Sphere *ball = new Sphere(Vec4(5, 7, 0), 1);
	ball->setColor(Colors::GREEN);

	Animated anim(p_iteration, ball, Vec4(-0.05, 0.0, -0.05));
	
	Light* light = new Light(Vec4(0, 10, -5));
	scene->addLight(light);

	// Render the scene
	scene->render(anim);
	end = std::chrono::steady_clock::now();

#ifdef _VERBOSE
	//std::cout << "scene #" << std::to_string(p_id) << " rendered in ";
	//std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.f << "ms" << std::endl;
	count += 1;
	if (count % 5 == 0)
		std::cout << "\rscenes " << count << "/" << FRAMES << " yet rendered";
#endif

#ifdef _SAVE_AS_FILE
	scene->save("scene_" + std::to_string(p_id));
#endif

	// We return the created texture
	FIBITMAP* img = scene->getFitbitMap();
	SDL_Surface* sdl_surface = get_sdl_surface(img, false);
	SDL_Texture* sdl_texture = get_sdl_texture(sdl_surface, sdl_renderer);
	FreeImage_Unload(img);

	return sdl_texture;
}

int main(int argc, char* argv[])
{
	// Multithreading is used to render images faster!
	SDL_Texture* rendered_imgs[FRAMES];
	std::vector<std::future<SDL_Texture*>> threads;
	std::chrono::steady_clock::time_point end, begin = std::chrono::steady_clock::now();

	// We create as much threads as we need images
	for (int i = 0; i < FRAMES; i++) {
		std::future<SDL_Texture*> ftre = std::async(render, i, i);
		threads.push_back(std::move(ftre));
	}

	std::cout << "main: all threads launched." << std::endl;

	// Join the results of all threads
	for (int i = 0; i < FRAMES; i++) {
		SDL_Texture* texture = threads[i].get();
		rendered_imgs[i] = texture;
	}

	end = std::chrono::steady_clock::now();
	std::cout << std::endl << FRAMES << " frames have been rendered in ";
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.f << "ms" << std::endl;
	std::cout << "lightning fast, isn't it ? " << std::endl;

	// Start the animation
	int index = 0;
	while (event_loop() == false)
	{
		render_image(rendered_imgs[index], sdl_renderer);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
		index = (index + 1) % FRAMES;
	}

	// Free SDL
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
