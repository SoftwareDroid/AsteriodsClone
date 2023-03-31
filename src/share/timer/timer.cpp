#include "timer.h"
#include <SDL2/SDL.h>

int Timer::get_ticks() const
{
        //If the timer is running
    if( started  )
    {
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}
Timer::Timer()
{
        //Initialize the variables
    startTicks = 0;

    started = false;
}

void Timer::start()
{
        //Start the timer
    started = true;


    //Get the current clock time
    startTicks = SDL_GetTicks();
}
