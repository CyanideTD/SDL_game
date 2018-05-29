#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include "timer.h"
#include <iostream>

using namespace std;

const int kMOUSE_OUT = 0;
const int kMOUSE_IN = 1;
const int kMOUSE_UP = 2;
const int kMOUSE_DOWN = 3;

const int kScreenWidth = 640;
const int kScreenHeight = 480;

const int kDotHeight = 20;
const int kDotWidth = 20;

const int kFramesPerSeconds = 20;

SDL_Window * window = NULL;
SDL_Surface * window_surface = NULL;
SDL_Surface * dot_surface = NULL;
Mix_Music * music = NULL;

Mix_Chunk * scratch = NULL;
Mix_Chunk * high = NULL;
Mix_Chunk * med = NULL;
Mix_Chunk * low = NULL;

TTF_Font * font = NULL;

SDL_Rect clips[4];

void SetClips()
{
    clips[kMOUSE_IN].x = 0;
    clips[kMOUSE_IN].y = 0;
    clips[kMOUSE_IN].w = 160;
    clips[kMOUSE_IN].h = 120;

    clips[kMOUSE_OUT].x = 160;
    clips[kMOUSE_OUT].y = 0;
    clips[kMOUSE_OUT].w = 160;
    clips[kMOUSE_OUT].h = 120;

    clips[kMOUSE_DOWN].x = 0;
    clips[kMOUSE_DOWN].y = 120;
    clips[kMOUSE_DOWN].w = 160;
    clips[kMOUSE_DOWN].h = 120;

    clips[kMOUSE_UP].x = 160;
    clips[kMOUSE_UP].y = 120;
    clips[kMOUSE_UP].w = 160;
    clips[kMOUSE_UP].h = 120;
}

void LoadImage(string filename)
{
    SDL_Surface* loadedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if (loadedImage != NULL)
    {
        dot_surface = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGBA32, 0);

        SDL_FreeSurface(loadedImage);
    }
}

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

class Dot
{
public:
    int x, y;
    int x_speed, y_speed;

public:
    Dot();
    void HandleEvent(const SDL_Event & event);
    void Move();
};

Dot::Dot()
{
    x = 0;
    y = 0;
    x_speed = 0;
    y_speed = 0;
}

void Dot::HandleEvent(const SDL_Event & event)
{

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.scancode)
        {
        case SDL_SCANCODE_UP:
            
            y_speed -= 10;
            break;
        case SDL_SCANCODE_DOWN:
            y_speed += 10;
            break;
        case SDL_SCANCODE_LEFT:
            x_speed -= 10;
            break;
        case SDL_SCANCODE_RIGHT:
            x_speed += 10;
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
            y_speed += 10;
            break;
        case SDL_SCANCODE_DOWN:
            y_speed -= 10;
            break;
        case SDL_SCANCODE_LEFT:
            x_speed += 10;
            break;
        case SDL_SCANCODE_RIGHT:
            x_speed -= 10;
            break;
        default:
            break;
        }
        printf("x_speed: %d \n", x_speed);
        printf("y_speed: %d \n", y_speed);
    }
}

void Dot::Move()
{
    x += x_speed;
    
    if (x < 0)
    {
        x = 0;
    }

    if (x > kScreenWidth - kDotWidth)
    {
        x = kScreenWidth - kDotWidth;
    }

    y += y_speed;

    if (y < 0)
    {
        y = 0;
    }

    if (y > kScreenHeight - kDotHeight)
    {
        y = kScreenHeight - kDotHeight;
    }
}




void Cleanup()
{
    SDL_FreeSurface(dot_surface);
    Mix_FreeChunk(scratch);
    Mix_FreeChunk(high);
    Mix_FreeChunk(med);
    Mix_FreeChunk(low);
    Mix_FreeMusic(music);

    TTF_CloseFont(font);

    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Color textColor = { 0, 0, 0 };

    if (TTF_Init() == -1)
    {
        return -1;
    }

    font = TTF_OpenFont("lazy.ttf", 28);

    SetClips();

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        return false;
    }

    music = Mix_LoadMUS("beat.wav");

    //如果加载音乐出了问题
    if (music == NULL)
    {
        return false;
    }

    //加载声效
    scratch = Mix_LoadWAV("scratch.wav");
    high = Mix_LoadWAV("high.wav");
    med = Mix_LoadWAV("medium.wav");
    low = Mix_LoadWAV("low.wav");

    window = SDL_CreateWindow("MyGame", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    window_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(window_surface, &window_surface->clip_rect, SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));

    //LoadImage("button.png");

    Dot dot;
    LoadImage("dot.bmp");

    bool quit = false;

    SDL_Event event;

    //button.ShowButton();

    Timer fps;

    Timer update;

    bool cap = false;

    int frames = 0;

    while (!quit)
    {
        fps.StartClock();
        while (SDL_PollEvent(&event))
        {
            dot.HandleEvent(event);
            frames++;
            std::cout << frames << endl;
        }
        dot.Move();
        SDL_FillRect(window_surface, &window_surface->clip_rect, SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));
        SDL_Rect rect;
        rect.x = dot.x;
        rect.y = dot.y;
        if (fps.GetTicks() < (1000 / kFramesPerSeconds))
        {
            SDL_Delay((1000 / kFramesPerSeconds) - fps.GetTicks());
            fps.StopClock();
        }
        SDL_BlitSurface(dot_surface, NULL, window_surface, &rect);
        SDL_UpdateWindowSurface(window);
    }

    return 0;
}

Button::Button()
{
    box.x = 170;
    box.y = 120;

    rect = &clips[kMOUSE_OUT];
}

Button::~Button()
{}

bool Button::HandleEvent(const SDL_Event &event)
{
    SDL_Rect * origin = rect;
    bool quit = false;
    int x = 0, y = 0;
    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        x = event.motion.x;
        y = event.motion.y;

        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            rect = &clips[kMOUSE_IN];
        }
        else
        {
            rect = &clips[kMOUSE_OUT];
        }
        break;
    case SDL_MOUSEBUTTONDOWN:

        x = event.motion.x;
        y = event.motion.y;

        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            rect = &clips[kMOUSE_DOWN];
        }
        break;

    case SDL_MOUSEBUTTONUP:
        x = event.motion.x;
        y = event.motion.y;
        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            rect = &clips[kMOUSE_UP];
        }
        break;
    default:
        printf("Error!!!!");
        return false;
        break;
    }

    if (origin != rect)
    {
        change = true;
    }

    return true;
}

bool Button::ShowButton()
{
    if (change = false)
    {
        return true;
    }

    SDL_BlitSurface(dot_surface, rect, window_surface, &box);

    SDL_UpdateWindowSurface(window);

    return true;
}