#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <string>

using namespace std;

const int kMOUSE_OUT = 0;
const int kMOUSE_IN = 1;
const int kMOUSE_UP = 2;
const int kMOUSE_DOWN = 3;

SDL_Window * window;
SDL_Surface * window_surface;
SDL_Surface * button_surface;

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
        button_surface = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGBA32, 0);

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

void Cleanup()
{
    SDL_FreeSurface(button_surface);
    SDL_Quit();
}

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Mix_Music * music = NULL;

    Mix_Chunk * scratch = NULL;
    Mix_Chunk * high = NULL;
    Mix_Chunk * med = NULL;
    Mix_Chunk * low = NULL;

    TTF_Font * font = NULL;
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

    window = SDL_CreateWindow("MyGame", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    window_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(window_surface, &window_surface->clip_rect, SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));

    //LoadImage("button.png");
    Button button;
    button_surface = TTF_RenderText_Solid(font, "The quick brown fox jumps", textColor);
    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    SDL_BlitSurface(button_surface, NULL, window_surface, &rect);
    SDL_UpdateWindowSurface(window);
    bool quit = false;

    SDL_Event event;

    //button.ShowButton();

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            //switch (event.type)
            //{
            //case SDL_QUIT:
            //    quit = true;
            //    printf("Press Quit");
            //    Cleanup();
            //    break;
            //default:
            //    button.HandleEvent(event);
            //    button.ShowButton();
            //    break;
            //}
        }
        const Uint8 *keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_LEFT])
        {
            button.rect = &clips[kMOUSE_OUT];
            button.change = true;
            button.ShowButton();
        }

        if (keystates[SDL_SCANCODE_RIGHT])
        {
            button.rect = &clips[kMOUSE_IN];
            button.change = true;
            button.ShowButton();
        }

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

    SDL_BlitSurface(button_surface, rect, window_surface, &box);

    SDL_UpdateWindowSurface(window);

    return true;
}