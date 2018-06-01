#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>
#include "timer.h"
#include <iostream>

const int kMOUSE_OUT = 0;
const int kMOUSE_IN = 1;
const int kMOUSE_UP = 2;
const int kMOUSE_DOWN = 3;

const int kScreenWidth = 640;
const int kScreenHeight = 480;

const int kDotHeight = 20;
const int kDotWidth = 20;

const int kFramesPerSeconds = 60;
extern SDL_Rect wall;

extern SDL_Window * window;
extern SDL_Surface * window_surface;
extern SDL_Surface * dot_surface;
extern Mix_Music * music;

extern Mix_Chunk * scratch;
extern Mix_Chunk * high;
extern Mix_Chunk * med;
extern Mix_Chunk * low;

extern TTF_Font * font;

extern SDL_Rect clips[4];
