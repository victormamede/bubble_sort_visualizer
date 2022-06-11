#pragma once
#include <SDL2/SDL_stdinc.h>

typedef struct
{
  int *values;
  int length;
  int focused;
  int selected;
  SDL_bool is_sorted;

} Data;