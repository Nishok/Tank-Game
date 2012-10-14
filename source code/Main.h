#ifndef _MAIN_H_
#define _MAIN_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream> //Stringstream - make strings out of multiple variables


#include "Define.h"
#include "Surfaces.h"
#include "Timer.h"

class CMain {
private:
	bool quit; //For the game itself
	bool running; //For the timer
	Uint32 start; //Timer's start value

	SDL_Surface* screen;
	SDL_Surface* background;
	SDL_Surface* image;
	SDL_Surface* dots;
	SDL_Surface* message;
	SDL_Surface* message1;
	SDL_Surface* message2;
	SDL_Surface* seconds;
	Mix_Music *music; //The playing music
	Mix_Chunk *scratch; //The sound effect
	Mix_Chunk *high;
	Mix_Chunk *med;
	Mix_Chunk *low;
	SDL_Rect clip[4];
	TTF_Font* font;
	SDL_Color textColor; //R, G, B
public:
	CMain();

	bool init();
	bool load_files();

	int OnExecute();
	int main(int argc, char* argv[]);

	void cleanup();
};


#endif