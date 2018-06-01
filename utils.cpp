#include "std_header.h"

SDL_Rect wall;

SDL_Window * window;
SDL_Surface * window_surface;
SDL_Surface * dot_surface;
Mix_Music * music;

Mix_Chunk * scratch;
Mix_Chunk * high;
Mix_Chunk * med;
Mix_Chunk * low;

TTF_Font * font;

SDL_Rect clips[4];