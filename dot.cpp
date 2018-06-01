#include "public.h"

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
}

void Dot::Move(Box & player1, Box & player2)
{
    int collision_code = Collision::CheckCollision(this, &player1);
    if (collision_code != 0)
    {
        rect.x -= x_speed;

        x_speed = -x_speed;
        y_speed += player1.GetSpeedY() / 2;
        return;
    }

    collision_code = Collision::CheckCollision(this, &player2);
    if (collision_code != 0)
    {
        rect.x -= x_speed;

        x_speed = -x_speed;
        y_speed += player2.GetSpeedY() / 2;
        return;
    }

    rect.x += x_speed;

    if (rect.x < 0)
    {
        rect.x = 0;
        x_speed = -x_speed;
        player2_score++;
        reset = true;
    }

    if (rect.x > kScreenWidth - kDotWidth)
    {
        rect.x = kScreenWidth - kDotWidth;
        x_speed = -x_speed;
        player1_score++;
        reset = true;
    }

    rect.y += y_speed;

    if (rect.y < 0)
    {
        rect.y = 0;
        y_speed = -y_speed;
    }

    if (rect.y > kScreenHeight - kDotHeight)
    {
        rect.y = kScreenHeight - kDotHeight;
        y_speed = -y_speed;
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

void Dot::SetSpeed(int x, int y)
{
    x_speed = x;
    y_speed = y;
}

void Dot::Display(SDL_Surface * window_surface)
{
    SDL_BlitSurface(surface, NULL, window_surface, &rect);
}

void Dot::SetSurface(SDL_Surface * image)
{
    surface = image;
}

void Dot::SetPos(int x, int y)
{
    rect.x = x;
    rect.y = y;
}
