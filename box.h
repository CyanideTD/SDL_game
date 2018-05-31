#pragma once
#include "std_header.h"
#include "public.h"

class Box : public Object
{
public:
    virtual void init(int x, int y);
    virtual void Move();
    virtual void Display(SDL_Surface* surface);
    virtual void CheckCollision(Dot * dot);
};