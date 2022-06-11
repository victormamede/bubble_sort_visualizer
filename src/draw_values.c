#include <stdio.h>
#include <SDL2/SDL.h>

#include "draw_values.h"

int get_max_value(int *values, int length)
{
  int max = -1;

  for (int i = 0; i < length; i++)
  {
    if (values[i] > max)
    {
      max = values[i];
    }
  }

  return max;
}

void draw_value(SDL_Renderer *renderer, int value, int index, DrawValuesSettings *settings, float y_scale_factor, int array_length)
{
  float step = settings->window_width / array_length;

  SDL_Rect rect;
  rect.x = settings->position_x + (index * step + settings->gap / 2);
  rect.w = step - settings->gap / 2;
  rect.y = settings->position_y + (settings->window_height - (value * y_scale_factor));
  rect.h = value * y_scale_factor;

  SDL_RenderFillRect(renderer, &rect);
}

void draw_values(SDL_Renderer *renderer, Data *data, DrawValuesSettings *settings)
{
  float y_scale_factor = (float)settings->window_height / get_max_value(data->values, data->length);

  for (int i = 0; i < data->length; i++)
  {
    if (data->is_sorted)
    {
      SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    }
    else if (i == data->selected)
    {
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
    }
    else if (i == data->focused)
    {
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    }
    else
    {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    }
    draw_value(renderer, data->values[i], i, settings, y_scale_factor, data->length);
  }
}