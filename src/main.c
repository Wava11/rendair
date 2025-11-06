#include "setup.h"
#include "renders.h"
#include <SDL.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

static const size_t NUM_BYTES_IN_FRAMEBUFFER =
    HEIGHT * WIDTH * sizeof(uint32_t);
static uint32_t V_PIXELS[NUM_BYTES_IN_FRAMEBUFFER];



void render(size_t frame_count, struct Screen* screen, void* pixels) {
  // render_running_square(frame_count, screen);
  render_line(screen);
  memcpy(pixels, screen->pixels, NUM_BYTES_IN_FRAMEBUFFER);
}

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("SDL_Init Error: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window = get_window(WIDTH, HEIGHT);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Texture *framebuffer =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  int running = 1;
  SDL_Event event;

  size_t frame_count = 0;
  struct Screen screen = {
    .pixels = V_PIXELS,
    .pitch = WIDTH * sizeof(uint32_t),
    .width = WIDTH,
    .height = HEIGHT,
  };

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = 0;
    }

    void *pixels;
    int pitch;
    SDL_LockTexture(framebuffer, NULL, &pixels, &pitch);

    render(frame_count, &screen, pixels);

    SDL_UnlockTexture(framebuffer);
    SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(16); // ~60 FPS
    frame_count++;
  }

  printf("Quitting...\n");
  SDL_DestroyTexture(framebuffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}