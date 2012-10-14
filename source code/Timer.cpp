#include "Timer.h"

CTimer::CTimer() 
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void CTimer::start() 
{
	started = true; //start the timer

	paused = false; //The timer is not paused, since it is started

	startTicks = SDL_GetTicks(); //Give startTicks the current SDL Ticks.
}

void CTimer::stop() 
{
	started = false; //Stop the timer

	paused = false; //The timer is not paused, since it is stoppped
}

void CTimer::pause() 
{
	if((started == true) && (paused == false))
	{
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void CTimer::unpause() 
{
	if(paused == true)
	{
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;

		pausedTicks = 0;
	}
}

int CTimer::getTicks() 
{
	if(started == true)
	{
		if(paused == true) return pausedTicks;
		else return SDL_GetTicks() - startTicks;
	}

	return 0; //If the timer isn't running
}

bool CTimer::is_started()
{
	return started;
}

bool CTimer::is_paused()
{
	return paused;
}
