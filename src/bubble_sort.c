#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_log.h>

#include "bubble_sort.h"
#include "data.h"

void bubble_sort(BubbleSortContext *context);

void bubble_process(float deltaTime, BubbleSortContext *context)
{
  while (context->time_to_update <= 0)
  {
    bubble_sort(context);
    context->time_to_update += context->update_interval;
  }

  context->time_to_update -= deltaTime;
}

void bubble_sort(BubbleSortContext *context)
{
  if (context->step >= context->data->length - 1)
  {
    if (context->swaps_made == 0)
    {
      context->data->is_sorted = SDL_TRUE;
    }

    context->step = 0;
    context->swaps_made = 0;
    context->iteration++;
  }

  if (context->data->is_sorted)
  {
    return;
  }

  int *values = context->data->values;
  int step = context->step;

  context->data->selected = step;
  context->data->focused = step + 1;

  if (values[step] > values[step + 1])
  {
    context->swaps_made++;
    int mem = values[step];
    values[step] = values[step + 1];
    values[step + 1] = mem;
  }

  context->step++;
}

BubbleSortContext *create_bubble_context(Data *data, float time_to_iterate)
{
  BubbleSortContext *scene = malloc(sizeof(BubbleSortContext));
  scene->iteration = 0;
  scene->step = 0;
  scene->swaps_made = 0;
  scene->data = data;
  scene->time_to_update = 0;
  scene->update_interval = time_to_iterate / data->length;

  return scene;
}