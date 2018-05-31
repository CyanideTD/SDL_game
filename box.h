#pragma once
#include "std_header.h"
#include "public.h"

class Box : public Object
{
public:
    virtual void init();
    virtual void Move();
    virtual void Display();
    virtual void CheckCollision(Dot * dot);
};