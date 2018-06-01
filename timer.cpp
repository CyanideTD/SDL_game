#include "public.h"

Timer::Timer()
{
    started = false;
    paused = false;

    start_ticks = 0;
    paused_ticks = 0;
}

int Timer::GetTicks()
{
    if (started == true)
    {
        if (paused == false)
        {
            return SDL_GetTicks() - start_ticks;
        }
        else
        {
            return paused_ticks;
        }
    }
    return 0;
}

void Timer::StartClock()
{
    if (!started)
    {
        started = true;
        start_ticks = SDL_GetTicks();
    }
}

void Timer::StopClock()
{
    started = false;
    start_ticks = 0;
    paused_ticks = 0;
    paused = false;
}

void Timer::PauseClock()
{
    if (started  && !paused)
    {
        paused = true;
        paused_ticks = SDL_GetTicks() - start_ticks;
    }
}

void Timer::RestartClock()
{
    if (paused)
    {
        paused = false;
        start_ticks = SDL_GetTicks() - paused_ticks;
        paused_ticks = 0;
    }
}