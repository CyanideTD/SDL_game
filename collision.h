#pragma once
#include "public.h"
class Dot;

class Collision
{
public:
    static int CheckCollision(Dot* dot, Box* box);
};