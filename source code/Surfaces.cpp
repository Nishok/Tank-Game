#include "Surfaces.h"

CSurface::CSurface() {
}

SDL_Surface* CSurface::load_image(string filename) //Load images normally, including transparent images. (BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA and PNG)
{
	SDL_Surface* loadedImage = NULL; //Temporary loaded image
	SDL_Surface* optimizedImage = NULL; // Temp image -> Optimized image
	loadedImage = IMG_Load(filename.c_str()); //Load image that is read from the string
	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormat(loadedImage); //Optimize it so it has the same bitrate as the screen
		SDL_FreeSurface(loadedImage); //Get rid of the old image
	}
	return optimizedImage; //Return the optimized one
}

SDL_Surface* CSurface::load_image_clrkey(string filename, int R, int G, int B) //Can load images with a background that need to be removed
{
	SDL_Surface* loadedImage = NULL; //Temporary loaded image
	SDL_Surface* optimizedImage = NULL; // Temp image -> Optimized image
	loadedImage = IMG_Load(filename.c_str()); //Load image that is read from the string
	if(loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage); //Optimize it so it has the same bitrate as the screen
		SDL_FreeSurface(loadedImage); //Get rid of the old image

		if(optimizedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, R, G, B); //Setting the color key.
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey); //Surface the colorkey needs to set to, SDL_SRCCOLORKEY is the flag to set the colorkey when blitting, then the collor we want to key.
		}
	}
	return optimizedImage; //Return the optimized one
}

void CSurface::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	//if(source == NULL || destination == NULL) {
    //    return false;
    //}

	SDL_Rect offset; //A temporary rectangle to hold the offset

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);

	//return true;
}