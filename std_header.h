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
SDL_Rect wall;

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
