#include "sdl.h"

/*
	DISCLAIMER: All rights to Tjelvar Olsson: (I just modified it a bit for my own purpose)
	http://tjelvarolsson.com/blog/how-to-build-a-basic-image-viewer-using-freeimage-and-sdl2/
*/


/** Initialise a SDL surface and return a pointer to it.
*
*  This function flips the FreeImage bitmap vertically to make it compatible
*  with SDL's coordinate system.
*
*  If the input image is in grayscale a custom palette is created for the
*  surface.
*/
SDL_Surface *get_sdl_surface(FIBITMAP *freeimage_bitmap, int is_grayscale) {

	// Loaded image is upside down, so flip it.
	FreeImage_FlipVertical(freeimage_bitmap);

	SDL_Surface *sdl_surface = SDL_CreateRGBSurfaceFrom(
		FreeImage_GetBits(freeimage_bitmap),
		FreeImage_GetWidth(freeimage_bitmap),
		FreeImage_GetHeight(freeimage_bitmap),
		FreeImage_GetBPP(freeimage_bitmap),
		FreeImage_GetPitch(freeimage_bitmap),
		FreeImage_GetRedMask(freeimage_bitmap),
		FreeImage_GetGreenMask(freeimage_bitmap),
		FreeImage_GetBlueMask(freeimage_bitmap),
		0
		);

	if (sdl_surface == NULL) {
		fprintf(stderr, "Failed to create surface: %s\n", SDL_GetError());
		exit(1);
	}

	if (is_grayscale) {
		// To display a grayscale image we need to create a custom palette.
		SDL_Color colors[256];
		int i;
		for (i = 0; i < 256; i++) {
			colors[i].r = colors[i].g = colors[i].b = i;
		}
		SDL_SetPaletteColors(sdl_surface->format->palette, colors, 0, 256);
	}

	return sdl_surface;
}

SDL_Texture* get_sdl_texture(SDL_Surface *surface, SDL_Renderer* renderer)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		fprintf(stderr, "Failed to load image as texture\n");
		exit(1);
	}

	return texture;
}


/** Initialise a SDL window and return a pointer to it. */
SDL_Window *get_sdl_window(int width, int height) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "SDL couldn't initialise: %s.\n", SDL_GetError());
		exit(1);
	}

	SDL_Window *sdl_window;
	sdl_window = SDL_CreateWindow("Raytracing",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

	return sdl_window;
}

SDL_Renderer* create_renderer(SDL_Window *window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_RenderClear(renderer);
	return renderer;
}

/** Display the image by rendering the surface as a texture in the window. */
void render_image(SDL_Texture *texture, SDL_Renderer *renderer)
{

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

/** Loop until a key is pressed. */
bool event_loop()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN) {
			return true;
		}
	}

	return false;
}



