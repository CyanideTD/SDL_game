#include "public.h"

const int kBoxHeight = 100;
const int kBoxWidth = 10;

void Box::init(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = kBoxWidth;
    rect.h = kBoxHeight;

    x_speed = 0;
    y_speed = 0;
}