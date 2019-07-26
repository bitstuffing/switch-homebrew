#pragma once

#include <SDL.h>

#define TITLE_BAR_SIZE 50

void draw_colored_rect(SDL_Renderer *renderer, int x, int y, int size_x, int size_y, int red, int green, int blue);
void draw_window(SDL_Renderer *renderer, int x, int y, int size_x, int size_y);

struct Window{
  SDL_Rect window;
  int x;
  int y;
  int size_x;
  int size_y;
  int red;
  int green;
  int blue;
  int display;
};
