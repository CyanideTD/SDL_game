#pragma once
#include "public.h"

const int kBoxHeight = 100;
const int kBoxWidth = 10;

class Box : public Object
{
public:
    virtual void init(int x, int y);
    virtual void Move();
    virtual void Display(SDL_Surface* surface);
    virtual SDL_Rect* GetRect();
    virtual void HandleEvent(const SDL_Event& event);
    virtual int GetSpeedX();
    virtual int GetSpeedY();
};