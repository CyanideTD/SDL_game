#include "public.h"

using namespace std;

bool CheckCollision(const SDL_Rect* box, const SDL_Rect* wall)
{
    int box_left = box->x;
    int box_right = box->x + box->w;
    int box_top = box->y;
    int box_bottom = box->y + box->h;

    int wall_left = wall->x;
    int wall_right = wall->x + wall->w;
    int wall_top = wall->y;
    int wall_bottom = wall->y + wall->h;

    if (box_left >= wall_right)
    {
        return false;
    }

    if (box_right <= wall_left)
    {
        return false;
    }

    if (box_top >= wall_bottom)
    {
        return false;
    }

    if (box_bottom <= wall_top)
    {
        return false;
    }

    return true;
}

bool CheckBoxesCollision(const vector<SDL_Rect> &boxes1, const vector<SDL_Rect> &boxes2)
{
    for (int i = 0; i < boxes1.size(); i++)
    {
        for (int j = 0; j < boxes2.size(); j++)
        {
            if (CheckCollision(&boxes1[i], &boxes2[j]))
            {
                return true;
            }
        }
    }
    return false;
}

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
        Uint32 colorkey = SDL_MapRGB(dot_surface->format, 0xFF, 0xFF, 0xFF);
        SDL_SetColorKey(dot_surface, SDL_TRUE, colorkey);
        SDL_FreeSurface(loadedImage);
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
    wall.x = 200;
    wall.y = 200;
    wall.h = 200;
    wall.w = 20;

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

    Dot ball(320, 240);
    LoadImage("dot.bmp");
    ball.SetSurface(dot_surface);
    ball.SetSpeed(10, 0);

    Box box;
    box.init(640 - kBoxWidth, 0);

    bool quit = false;

    SDL_Event event;

    Timer fps;

    Timer update;

    bool cap = false;

    int frames = 0;

    while (!quit)
    {
        fps.StartClock();
        int i = 0;
        while (i < 10 && SDL_PollEvent(&event))
        {
            i++;
            box.HandleEvent(event);
            frames++;
            std::cout << frames << endl;
        }
        box.Move();
        ball.Move(box);
        SDL_FillRect(window_surface, &window_surface->clip_rect, SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));
        box.Display(window_surface);
        ball.Display(window_surface);
        //TODO fps change
        if (fps.GetTicks() < (1000 / kFramesPerSeconds))
        {
            SDL_Delay((1000 / kFramesPerSeconds) - fps.GetTicks());
            fps.StopClock();
        }

        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
