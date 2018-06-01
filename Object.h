#pragma once
#include "public.h"

class Object
{
protected:
    SDL_Rect rect;
    int x_speed, y_speed;

public:
    virtual void init(int x, int y) = 0;
    virtual void Move() = 0;
    virtual void Display(SDL_Surface* surface) = 0;
};
