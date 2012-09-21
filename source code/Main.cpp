#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>
#include "Main.h"
#include "Define.h"
#include <string>
#include <sstream> //Stringstream - make strings out of multiple variables

using namespace std;

//Initialization
SDL_Surface* screen = NULL;
SDL_Surface* background = NULL;
SDL_Surface* image = NULL;
SDL_Surface* dots = NULL;
SDL_Surface* message = NULL;
SDL_Surface* message1 = NULL;
SDL_Surface* message2 = NULL;
SDL_Surface* seconds = NULL;
Mix_Music *music = NULL; //The playing music
Mix_Chunk *scratch = NULL; //The sound effect
Mix_Chunk *high = NULL;
Mix_Chunk *med = NULL;
Mix_Chunk *low = NULL;
SDL_Event event; //Load the event structures
SDL_Rect clip[4];
TTF_Font* font = NULL;
SDL_Color textColor = { 0, 0, 0 }; //R, G, B

SDL_Surface* load_image(string filename) //Load images normally, including transparent images. (BMP, PNM, XPM, LBM, PCX, GIF, JPEG, TGA and PNG)
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

SDL_Surface* load_image_clrkey(string filename, int R, int G, int B) //Can load images with a background that need to be removed
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

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
	SDL_Rect offset; //A temporary rectangle to hold the offset

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, clip, destination, &offset);
}

bool init()
{
	if(SDL_Init( SDL_INIT_EVERYTHING ) == -1) //Start the SDL and everything inside it (soundmixer, etc)
	{
		return false;
	}

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_SWSURFACE); //Setup the screen
	if(screen == NULL)
	{
		return false;
	}

	if(TTF_Init() == -1)
	{
		return false;
	}

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		return false;
	}

	SDL_WM_SetCaption("Nishok's test game", NULL); //Window title and icon

	return true;
}

bool load_files()
{
	if((background = load_image("images/background.bmp")) == NULL) //Load image
	{
		return false;
	}

	if((image = load_image("images/hello.bmp")) == NULL)
	{
		return false;
	}

	if((dots = load_image("images/dots.jpg")) == NULL)
	{
		return false;
	}

	if((font = TTF_OpenFont("lazy.ttf", 28)) == NULL) //Load TTF file and set font size
	{
		return false;
	}

	music = Mix_LoadMUS("beat.wav");
	scratch = Mix_LoadWAV("scratch.wav");
	high = Mix_LoadWAV("high.wav");
	med = Mix_LoadWAV("medium.wav");
	low = Mix_LoadWAV("low.wav");

	if((music == NULL) || (scratch == NULL) || (high == NULL) || (med == NULL) || (low == NULL))
	{
		return false;
	}

	return true;
}

void cleanup()
{
	SDL_FreeSurface(background); //Free the surface
	SDL_FreeSurface(image);
	SDL_FreeSurface(dots);
	SDL_FreeSurface(message);
	SDL_FreeSurface(message1);
	SDL_FreeSurface(message2);
	SDL_FreeSurface(seconds);

	Mix_FreeChunk(scratch);
	Mix_FreeChunk(high);
	Mix_FreeChunk(med);
	Mix_FreeChunk(low);
	Mix_FreeMusic(music);

	TTF_CloseFont(font);
	TTF_Quit();

	SDL_Quit(); //Quit the SDL
}

int main( int argc, char* argv[] )
{
	bool quit = false;

	bool running = true; //For the timer

	Uint32 start = 0;

	start = SDL_GetTicks();

	if(init() == false)
	{
		return 1;
	}

	if(load_files() == false)
	{
		return 2;
	}

	message1 = TTF_RenderText_Solid(font, "You mad? Yep, you are.", textColor); //font-file, text, color
	message2 = TTF_RenderText_Solid(font, "You mad? Oh, you aren't? :(.", textColor);

	if(message1 == false || message2 == false)
	{
		return 3;
	}

	while(quit == false)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				switch( event.key.keysym.sym )
				{
					case SDLK_UP: message = message1; break;
					case SDLK_DOWN: message = message2; break;
					case SDLK_1: if(Mix_PlayChannel(-1, high, 0) == -1) //channel (-1 = first available channel), Mix_Chunk(), repeat (-1 = infinite)
								 {
									return 1;
								 }
					case SDLK_2: if(Mix_PlayChannel(-1, med, 0) == -1)
								 {
									return 1;
								 };  break;
					case SDLK_3: if(Mix_PlayChannel(-1, low, 0) == -1)
								 {
									return 1;
								 }  break;
					case SDLK_4: if(Mix_PlayingMusic() == 0)
								 {
									if(Mix_PlayMusic(music, -1) == -1) //music, repeat
									{
										return 1;
									}
								 } 
								 else
								 {
									 if(Mix_PausedMusic() == 1)
									 {
										Mix_ResumeMusic();
									 }
									 else
									 {
										Mix_PauseMusic();
									 }
								 }  break;
					case SDLK_0: Mix_HaltMusic();  break;
					case SDLK_s: if(running == true)
								 {
									running = false;
									start = 0;
								 }
								 else
								 {
									running = true;
									start = SDL_GetTicks();
								 }  break;
				}
			}
			else if(event.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		if(running == true)
		{
			stringstream time;
			time << "Timer: " << SDL_GetTicks() - start;

			seconds = TTF_RenderText_Solid(font, time.str().c_str(), textColor);
		}

		apply_surface(0, 0, background, screen); //X, Y, source, destination
		apply_surface(320, 0, background, screen);
		apply_surface(0, 240, background, screen);
		apply_surface(320, 240, background, screen);
		apply_surface(180, 140, image, screen);
		apply_surface((SCREEN_WIDTH - seconds->w) / 2, 25, seconds, screen);

		if(message != NULL)
		{
			apply_surface(100, 0, message, screen);
			message = NULL;
		}

		clip[ 0 ].x = 0; 
		clip[ 0 ].y = 0; 
		clip[ 0 ].w = 100; 
		clip[ 0 ].h = 100; 
		
		clip[ 1 ].x = 100; 
		clip[ 1 ].y = 0; 
		clip[ 1 ].w = 100; 
		clip[ 1 ].h = 100; 

		clip[ 2 ].x = 0; 
		clip[ 2 ].y = 100; 
		clip[ 2 ].w = 100; 
		clip[ 2 ].h = 100; 

		clip[ 3 ].x = 100; 
		clip[ 3 ].y = 100; 
		clip[ 3 ].w = 100; 
		clip[ 3 ].h = 100; 

		apply_surface( 0, 0, dots, screen, &clip[ 0 ] ); //X, Y, source, destination, rectangle of which to copy
		apply_surface( 540, 0, dots, screen, &clip[ 1 ] );
		apply_surface( 0, 380, dots, screen, &clip[ 2 ] );
		apply_surface( 540, 380, dots, screen, &clip[ 3 ] );

		if(SDL_Flip(screen) == -1) //Refresh the screen
		{
			return 4;
		}
	}

	cleanup();

	return 0;
}
