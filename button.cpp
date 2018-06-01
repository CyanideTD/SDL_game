#include "public.h"

Button::Button()
{
    box.x = 170;
    box.y = 120;

    rect = &clips[kMOUSE_OUT];
}

Button::~Button()
{}

bool Button::HandleEvent(const SDL_Event &event)
{
    SDL_Rect * origin = rect;
    bool quit = false;
    int x = 0, y = 0;
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        x = event.motion.x;
        y = event.motion.y;

        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            rect = &clips[kMOUSE_IN];
        }
        else
        {
            rect = &clips[kMOUSE_OUT];
        }
        break;
    case SDL_MOUSEBUTTONDOWN:

        x = event.motion.x;
        y = event.motion.y;

        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            rect = &clips[kMOUSE_DOWN];
        }
        break;

    case SDL_MOUSEBUTTONUP:
        x = event.motion.x;
        y = event.motion.y;
        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            rect = &clips[kMOUSE_UP];
        }
        break;
    default:
        printf("Error!!!!");
        return false;
        break;
    }

    if (origin != rect)
    {
        change = true;
    }

    return true;
}

bool Button::ShowButton()
{
    if (change = false)
    {
        return true;
    }

    SDL_BlitSurface(dot_surface, rect, window_surface, &box);

    SDL_UpdateWindowSurface(window);

    return true;
}

