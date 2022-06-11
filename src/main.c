#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "draw_values.h"
#include "bubble_sort.h"
#include "data.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 400
#define NUMBER_COUNT 10
#define MAX_NUMBER 100

Data *generate_random_data();

int main()
{
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
  {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Window *win = SDL_CreateWindow("Sorter!",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     WINDOW_WIDTH,
                                     WINDOW_HEIGHT,
                                     SDL_WINDOW_SHOWN);
  if (win == NULL)
  {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == NULL)
  {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_FAILURE;
  }

  double lastTime = SDL_GetTicks();

  DrawValuesSettings settings;
  settings.gap = 2.0;
  settings.position_x = 0;
  settings.position_y = 200;
  settings.window_height = WINDOW_HEIGHT - 200;
  settings.window_width = WINDOW_WIDTH;

  Data *data = generate_random_data();
  BubbleSortContext *bubble_context = create_bubble_context(data, 1000);

  SDL_bool isRunning = SDL_TRUE;
  while (isRunning)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      // Handle events
      if (event.type == SDL_QUIT)
      {
        isRunning = SDL_FALSE;
      }

      if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
      {
        free(data->values);
        free(data);
        free(bubble_context);
        data = generate_random_data();
        bubble_context = create_bubble_context(data, 1000);
      }
    }

    // Calculate deltaTime
    double startTime = SDL_GetTicks();
    double deltaTime = startTime - lastTime;
    lastTime = startTime;

    // Handle updates
    bubble_process(deltaTime, bubble_context);

    // Clear screen and draw
    SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(ren);

    draw_values(ren, data, &settings);

    SDL_RenderPresent(ren);
  }

  free(bubble_context);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return EXIT_SUCCESS;
}

Data *generate_random_data()
{
  int *values = calloc(NUMBER_COUNT, sizeof(int));
  for (int i = 0; i < NUMBER_COUNT; i++)
  {
    values[i] = rand() % MAX_NUMBER;
  }

  Data *data = malloc(sizeof(Data));
  data->focused = -1;
  data->selected = -1;
  data->length = NUMBER_COUNT;
  data->values = values;
  data->is_sorted = SDL_FALSE;

  return data;
}