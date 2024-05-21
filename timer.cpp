// timer.cpp
#include "timer.hpp"

// Based on Lazyfoo's timer tutorial

Timer::Timer()
{
    //Initialize the variables
    startingTime = 0;
    pausedTime = 0;

    statePaused = false;
    stateStarted = false;
}

void Timer::start()
{
    //Start the timer
    stateStarted= true;

    //Unpause the timer
    statePaused = false;

    //Get the current clock time
    startingTime = SDL_GetTicks();
    pausedTime = 0;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( stateStarted && !statePaused )
    {
        //Pause the timer
        statePaused = true;

        //Calculate the paused ticks
        pausedTime = SDL_GetTicks() - startingTime;
        startingTime = 0;
    }
}

void Timer::unpause()
{
    //If the timer is running and paused
    if( stateStarted && statePaused )
    {
        //Unpause the timer
        statePaused = false;

        //Reset the starting ticks
        startingTime = SDL_GetTicks() - pausedTime;

        //Reset the paused ticks
        pausedTime = 0;
    }
}

void Timer::stop()
{
    //Stop the timer
    stateStarted = false;

    //Unpause the timer
    statePaused = false;

    //Clear tick variables
    startingTime = 0;
    pausedTime = 0;
}

unsigned int Timer::getTime()
{
    //The actual timer time
    unsigned int time = 0;

    //If the timer is running
    if( stateStarted )
    {
        //If the timer is paused
        if( statePaused )
        {
            //Return the number of ticks when the timer was paused
            time = pausedTime;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - startingTime;
        }
    }

    return time;
}

bool Timer::isStarted()
{
    return stateStarted;
}

bool Timer::isPaused()
{
    return statePaused && stateStarted;
}