#pragma once
#include "std_header.h"

class Button
{
public:
    Button();
    ~Button();
    bool HandleEvent(const SDL_Event &event);
    bool ShowButton();
public:
    SDL_Rect * rect;
    SDL_Rect box;
    bool change = false;
};