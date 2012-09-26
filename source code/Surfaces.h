#ifndef _SURFACES_H_
#define _SURFACES_H_

#include "SDL.h"
#include "SDL_image.h"
#include <string>

using namespace std;

class CSurface {
public:
	CSurface();

	static SDL_Surface* load_image(string filename); //Load images normally, including transparent images. (BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA and PNG)

	static SDL_Surface* load_image_clrkey(string filename, int R, int G, int B); //Can load images with a background that need to be removed

	static void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL); //Applies the surface
};

#endif