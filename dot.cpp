#include "dot.h"
#include "SDL.h"
#include "stdio.h"
#include "std_header.h"

Dot::Dot(int x, int y)
{
    rect.x = x;
    rect.y = y;

    x_speed = 0;
    y_speed = 0;

    collision_box.resize(11);

    collision_box[0].w = 6;
    collision_box[0].h = 1;

    collision_box[1].w = 10;
    collision_box[1].h = 1;

    collision_box[2].w = 14;
    collision_box[2].h = 1;

    collision_box[3].w = 16;
    collision_box[3].h = 2;

    collision_box[4].w = 18;
    collision_box[4].h = 2;

    collision_box[5].w = 20;
    collision_box[5].h = 6;

    collision_box[6].w = 18;
    collision_box[6].h = 2;

    collision_box[7].w = 16;
    collision_box[7].h = 2;

    collision_box[8].w = 14;
    collision_box[8].h = 1;

    collision_box[9].w = 10;
    collision_box[9].h = 1;

    collision_box[10].w = 6;
    collision_box[10].h = 1;

    ShiftBox();
}

void Dot::HandleEvent(const SDL_Event & event)
{

    if (event.type == SDL_KEYDOWN)
    {
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            if (y_speed == 0)
            {
                y_speed -= 1;
            }
            break;
        case SDL_SCANCODE_DOWN:
            if (y_speed == 0)
            {
                y_speed += 1;
            }
            break;
        case SDL_SCANCODE_LEFT:
            if (x_speed == 0)
            {
                x_speed -= 1;
            }
            break;
        case SDL_SCANCODE_RIGHT:
            if (x_speed == 0)
            {
                x_speed += 1;
            }
            break;
        default:
            break;
        }
        printf("x_speed: %d \n", x_speed);
        printf("y_speed: %d \n", y_speed);
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            if (y_speed < 0)
            {
                y_speed += 1;
            }
            break;
        case SDL_SCANCODE_DOWN:
            if (y_speed > 0)
            {
                y_speed -= 1;
            }
            break;
        case SDL_SCANCODE_LEFT:
            if (x_speed < 0)
            {
                x_speed += 1;
            }
            break;
        case SDL_SCANCODE_RIGHT:
            if (x_speed > 0)
            {
                x_speed -= 1;
            }
            break;
        default:
            break;
        }
        printf("x_speed: %d \n", x_speed);
        printf("y_speed: %d \n", y_speed);
    }
}

void Dot::Move(const Dot & dot)
{
    rect.x += x_speed;

    if (rect.x < 0)
    {
        rect.x = 0;
    }

    if (rect.x > kScreenWidth - kDotWidth)
    {
        rect.x = kScreenWidth - kDotWidth;
    }

    rect.y += y_speed;

    if (rect.y < 0)
    {
        rect.y = 0;
    }

    if (rect.y > kScreenHeight - kDotHeight)
    {
        rect.y = kScreenHeight - kDotHeight;
    }

    ShiftBox();

    if (CheckBoxesCollision(collision_box, dot.collision_box))
    {
        rect.x -= x_speed;
        rect.y -= y_speed;
    }
}

void Dot::ShiftBox()
{
    int x = rect.x;
    int y = rect.y;
    int r = 0;
    for (int set = 0; set < collision_box.size(); set++)
    {
        collision_box[set].x = x + (kDotWidth - collision_box[set].w) / 2;
        collision_box[set].y = y + r;
        r += collision_box[set].h;
    }
}