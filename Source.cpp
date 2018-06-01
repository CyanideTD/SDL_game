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

int player1_score = 0;
int player2_score = 0;
bool reset = true;

int main(int argc, char* args[])
{
    SDL_Surface* score1 = NULL;
    SDL_Surface* score2 = NULL;

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
    ball.SetSpeed(1, 0);

    Box player1;
    player1.init(640 - kBoxWidth, 0, SDL_SCANCODE_W, SDL_SCANCODE_S);

    Box player2;
    player2.init(0, 0, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
    bool quit = false;

    SDL_Event event;

    Timer fps;

    Timer update;

    bool cap = false;

    int frames = 0;

    while (!quit)
    {
        fps.start();
        update.start();
        if (reset)
        {
            player2.init(20, 200, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);
            player1.init(620 - kBoxWidth, 200, SDL_SCANCODE_W, SDL_SCANCODE_S);
            ball.SetPos(320, 240);
            ball.SetSpeed(2, 0);
            reset = false;
        }
        frames++;
        while (SDL_PollEvent(&event))
        {
            player1.HandleEvent(event);
            player2.HandleEvent(event);
        }
        if (update.get_ticks() > 1000)
        {
            int average = frames / (update.get_ticks() / 1000.f);
            stringstream ss;
            ss << average;
            SDL_SetWindowTitle(window, ss.str().c_str());
            frames = 0;
        }
        player1.Move();
        player2.Move();
        ball.Move(player1, player2);
        SDL_FillRect(window_surface, &window_surface->clip_rect, SDL_MapRGB(window_surface->format, 0xFF, 0xFF, 0xFF));
        //TODO fps change
        if (fps.get_ticks() < (1000 / kFramesPerSeconds))
        {
            SDL_Delay((1000 / kFramesPerSeconds) - fps.get_ticks());
        }
        player1.Display(window_surface);
        player2.Display(window_surface);
        ball.Display(window_surface);

        stringstream ss;
        ss << player1_score;
        score1 = TTF_RenderText_Solid(font, ss.str().c_str(), textColor);
        stringstream st;
        st << player2_score;
        score2 = TTF_RenderText_Solid(font, st.str().c_str(), textColor);
        SDL_Rect rect;
        rect.x = 100;
        rect.y = 0;
        SDL_BlitSurface(score1, NULL, window_surface, &rect);
        SDL_FreeSurface(score1);

        rect.x = 540;
        SDL_BlitSurface(score2, NULL, window_surface, &rect);
        SDL_FreeSurface(score2);
        SDL_UpdateWindowSurface(window);
    }

    return 0;
}
