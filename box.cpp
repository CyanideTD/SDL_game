#include "public.h"

void Box::init(int x, int y, int u, int d)
{
    rect.x = x;
    rect.y = y;
    rect.w = kBoxWidth;
    rect.h = kBoxHeight;
   
    up_key = u;
    down_key = d;

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
        if (event.key.keysym.scancode == up_key)
        {
            if (y_speed == 0)
            {
                y_speed -= 10;
            }
        }
        else if (event.key.keysym.scancode == down_key)
        {
            if (y_speed == 0)
            {
                y_speed += 10;
            }
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        if (event.key.keysym.scancode == up_key)
        {
            if (y_speed != 0)
            {
                y_speed += 10;
            }
        }
        else if (event.key.keysym.scancode == down_key)
        {
            if (y_speed != 0)
            {
                y_speed -= 10;
            }
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

