#pragma once
#include "public.h"

class Timer
{
private:
    int start_ticks;
    int paused_ticks;

    bool started;
    bool paused;

public:
    void StartClock();
    void StopClock();
    void PauseClock();
    void RestartClock();

    int GetTicks();

    bool IsStarted()
    {
        return started;
    }
    bool IsPaused()
    {
        return paused;
    }

    Timer();
};
