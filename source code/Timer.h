#ifndef _TIMER_H_
#define _TIMER_H_

#include "SDL.h"

class CTimer 
{
private: 
	int startTicks; //Tick amount when the clock was started
	int pausedTicks; //Tick amount when paused
	bool paused; //If timer paused
	bool started; //if timer started

public: 
	CTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	int getTicks(); //Get the current tick amount

	bool is_started();
	bool is_paused();
};

#endif