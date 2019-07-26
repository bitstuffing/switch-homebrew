#include <SDL.h>
#include "controls.h"

void draw_colored_rect(SDL_Renderer *renderer, int x, int y, int size_x, int size_y, int red, int green, int blue){
    SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
    SDL_Rect r = {x, y, size_x, size_y};
    SDL_RenderFillRect(renderer, &r);
}

void draw_window(SDL_Renderer *renderer, int x, int y, int size_x, int size_y){
  struct Window win = {
    {x, y, size_x, size_y}, x, y, size_x, size_y, 0, 0, 255, 1
  };
  SDL_Rect window = {win.x, win.y, win.size_x, win.size_y};
  SDL_RenderDrawRect(renderer,&window);
  SDL_Rect r = {win.x, win.y, win.size_x, TITLE_BAR_SIZE};
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  SDL_RenderFillRect(renderer, &r);
}
