#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <FreeImage.h>

/*
	DISCLAIMER: All rights to Tjelvar Olsson:
	http://tjelvarolsson.com/blog/how-to-build-a-basic-image-viewer-using-freeimage-and-sdl2/
*/


SDL_Surface *get_sdl_surface(FIBITMAP *freeimage_bitmap, int is_grayscale);
SDL_Window *get_sdl_window(int width, int height);
void render_image(SDL_Window *window, SDL_Surface *surface);
void event_loop();