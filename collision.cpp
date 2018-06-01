#include "public.h"

int Collision::CheckCollision(Dot * dot, Box * box)
{
    int center_x = dot->rect.x + kDotWidth / 2;
    int center_y = dot->rect.y + kDotHeight / 2;

    int ridus = kDotHeight / 2;

    SDL_Rect* rect = box->GetRect();


    if (center_x >= rect->x + rect->w)
    {
        if (center_x - (rect->x + rect->w) > ridus)
        {
            return 0;
        }
    }

    if (center_x <= rect->x)
    {
        if (rect->x - center_x > ridus)
        {
            return 0;
        }
    }

    if (center_y >= rect->y + rect->w && center_y - (rect->y + rect->w) > ridus)
    {
        return 0;
    }

    if (center_y < rect->y &&  rect->y - center_y > ridus)
    {
        return 0;
    }

    return 1;

}