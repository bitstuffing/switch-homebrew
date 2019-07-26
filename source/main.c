#include <stdlib.h>
#include <stdio.h>

#include <SDL.h>

#include "controls.h"

#define MAX_CONTROL 192
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

static int w = SCREEN_WIDTH, h = SCREEN_HEIGHT;
static SDL_Renderer *renderer;

float touch_x = 30.0, touch_y = 30.0;

void draw_rects(int x, int y){
    draw_colored_rect(renderer, x, y, 64, 64, 255,0,0); // R
    draw_colored_rect(renderer, x+64, y, 64, 64, 0,255,0); // G
    draw_colored_rect(renderer, x+128, y, 64, 64, 0,0,255); // B

    draw_window(renderer, touch_x, touch_y, 360, 360);
}

int manage_event(SDL_Event event,SDL_Window *window){
  int done = 0;

  switch (event.type) {
      case SDL_FINGERMOTION:
        printf("%d - %d",event.tfinger.x,event.tfinger.y);
        touch_x = event.tfinger.x*SCREEN_WIDTH;
        touch_y = event.tfinger.y*SCREEN_HEIGHT;
        break;
      case SDL_JOYAXISMOTION:
          SDL_Log("Joystick %d axis %d value: %d\n",
                  event.jaxis.which,
                  event.jaxis.axis, event.jaxis.value);
          break;

      case SDL_JOYBUTTONDOWN:
          SDL_Log("Joystick %d button %d down\n",
                  event.jbutton.which, event.jbutton.button);
          // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L52
          // seek for joystick #0
          if (event.jbutton.which == 0) {
              if (event.jbutton.button == 0) { // (A) button down

              } else if (event.jbutton.button == 10) {
                  // (+) button down
                  done = 1;
              }
          }
          break;

      default:
          break;
  }
  return done;
}

int main(int argc, char *argv[]){

    SDL_Event event;
    SDL_Window *window;
    int done = 0, x = 0;

    // mandatory at least on switch, else gfx is not properly closed
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        SDL_Log("SDL_Init: %s\n", SDL_GetError());
        return -1;
    }

    // create an SDL window (OpenGL ES2 always enabled)
    // when SDL_FULLSCREEN flag is not set, viewport is automatically handled by SDL (use SDL_SetWindowSize to "change resolution")
    // available switch SDL2 video modes :
    // 1920 x 1080 @ 32 bpp (SDL_PIXELFORMAT_RGBA8888)
    // 1280 x 720 @ 32 bpp (SDL_PIXELFORMAT_RGBA8888)
    window = SDL_CreateWindow("sdl2_gles2", 0, 0, 1920, 1080, 0);
    if (!window) {
        SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // create a renderer (OpenGL ES2)
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // open CONTROLLER_PLAYER_1 and CONTROLLER_PLAYER_2
    // when railed, both joycons are mapped to joystick #0,
    // else joycons are individually mapped to joystick #0, joystick #1, ...
    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L45
    for (int i = 0; i < 2; i++) {
        if (SDL_JoystickOpen(i) == NULL) {
            SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
            SDL_Quit();
            return -1;
        }
    }

    while (!done) {
        while (SDL_PollEvent(&event)) {
            done = manage_event(event,window);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // fill window bounds
        SDL_SetRenderDrawColor(renderer, 111, 111, 111, 255);
        SDL_GetWindowSize(window, &w, &h);
        SDL_Rect f = {0, 0, w, h};
        SDL_RenderFillRect(renderer, &f);

        draw_rects(x, 0);
        draw_rects(x, h - 64);

        SDL_RenderPresent(renderer);

        x++;
        if (x > w - MAX_CONTROL) {
            x = 0;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
