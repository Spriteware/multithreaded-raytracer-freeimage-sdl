#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <FreeImage.h>

/*
	DISCLAIMER: All rights to Tjelvar Olsson: (I just modified it a bit for my own purpose)
	http://tjelvarolsson.com/blog/how-to-build-a-basic-image-viewer-using-freeimage-and-sdl2/
*/


SDL_Surface *get_sdl_surface(FIBITMAP *freeimage_bitmap, int is_grayscale);
SDL_Texture* get_sdl_texture(SDL_Surface *surface, SDL_Renderer* renderer);
SDL_Window *get_sdl_window(int width, int height);
SDL_Renderer* create_renderer(SDL_Window *window);
void render_image(SDL_Texture *texture, SDL_Renderer *renderer);
bool event_loop();