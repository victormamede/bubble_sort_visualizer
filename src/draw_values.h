#pragma once
#include <SDL2/SDL.h>
#include "data.h"

typedef struct
{
  int position_x;
  int position_y;
  int window_width;
  int window_height;
  int gap;
} DrawValuesSettings;

void draw_values(SDL_Renderer *renderer, Data *values, DrawValuesSettings *settings);