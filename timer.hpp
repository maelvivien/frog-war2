#ifndef TIMER_HPP
#define TIMER_HPP
// Based on Lazyfoo's timer tutorial
#include <SDL2/SDL_timer.h>

class Timer {
public:

    Timer();

    void start();

    // Clear Timer
    void stop();

    // Pause the timer while keeping track of the time
    void pause();
    void unpause();

    void reset();

    unsigned int getTime();

    bool isStarted();
    bool isPaused();

private:
    // Variable keeping the starting time
    unsigned int startingTime;

    // Variable keeping the pause duration
    unsigned int pausedTime;

    // Status of the timer
    bool statePaused;
    bool stateStarted;
};


#endif // TIMER_HPP