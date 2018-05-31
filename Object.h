#pragma once
#include "std_header.h"

class Object
{
protected:
    SDL_Rect rect;
    int x_speed, y_speed;

public:
    virtual void init() = 0;
    virtual void Move() = 0;
    virtual void Display() = 0;
    virtual void CheckCollision(Object * object) = 0;
};
