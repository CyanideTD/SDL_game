#include "public.h"

void Box::init(int x, int y, int u, int d)
{
    rect.x = x;
    rect.y = y;
    rect.w = kBoxWidth;
    rect.h = kBoxHeight;
    
    up = u;
    down = d;

    x_speed = 0;
    y_speed = 0;
}

SDL_Rect* Box::GetRect()
{
    return &rect;
}

void Box::Display(SDL_Surface* window_surface)
{
    if (window_surface == NULL)
    {
        return;
    }

    SDL_FillRect(window_surface, &rect, SDL_MapRGB(window_surface->format, 0, 0, 0));

    return;
}

void Box::HandleEvent(const SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            if (y_speed == 0)
            {
                y_speed -= 10;
            }
            break;
        case SDL_SCANCODE_DOWN:
            if (y_speed == 0)
            {
                y_speed += 10;
            }
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            if (y_speed < 0)
            {
                y_speed += 10;
            }
            break;
        case SDL_SCANCODE_DOWN:
            if (y_speed > 0)
            {
                y_speed -= 10;
            }
            break;
        default:
            break;
        }
    }
}

int Box::GetSpeedX()
{
    return x_speed;
}

int Box::GetSpeedY()
{
    return y_speed;
}

void Box::Move()
{
    rect.y += y_speed;

    if (rect.y < 0)
    {
        rect.y = 0;
    }

    if (rect.y > kScreenHeight - rect.h)
    {
        rect.y = kScreenHeight - rect.h;
    }
}

