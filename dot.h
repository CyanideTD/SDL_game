#pragma once
#include "public.h"

class Box;

class Dot
{
public:
    SDL_Rect rect;

    SDL_Surface* surface;

    std::vector<SDL_Rect> collision_box;

    int x_speed, y_speed;

public:
    Dot(int x, int y);
    void HandleEvent(const SDL_Event & event);
    void Move(Box & box);
    void ShiftBox();
    void SetSpeed(int x, int y);
    void Display(SDL_Surface* surface);
    void SetSurface(SDL_Surface * image);
};
