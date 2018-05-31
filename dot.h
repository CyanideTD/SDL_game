#pragma once
#include "std_header.h"

class Dot
{
public:
    SDL_Rect rect;

    std::vector<SDL_Rect> collision_box;

    int x_speed, y_speed;

public:
    Dot(int x, int y);
    void HandleEvent(const SDL_Event & event);
    void Move(const Dot & dot);
    void ShiftBox();
};
