#pragma once
#include "data.h"

typedef struct
{
  Data *data;
  int step;
  int iteration;
  int swaps_made;

  float update_interval;
  float time_to_update;
} BubbleSortContext;

void bubble_process(float deltaTime, BubbleSortContext *context);

BubbleSortContext *create_bubble_context(Data *data, float time_to_iterate);