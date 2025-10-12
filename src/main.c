#include "setup.h"
#include <SDL.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

static const size_t NUM_BYTES_IN_FRAMEBUFFER =
    HEIGHT * WIDTH * sizeof(uint32_t);
static uint32_t V_PIXELS[NUM_BYTES_IN_FRAMEBUFFER];

#define set_pixel(pixels, pitch, x, y, color)                                  \
  ((uint32_t *)((uint8_t *)pixels + y * pitch))[x] = color;

void draw_square(void *pixels, int pitch, size_t top_left_x, size_t top_left_y,
                 size_t length, uint32_t color) {
  for (size_t i = 0; i < length; i++) {
    for (size_t j = 0; j < length; j++) {
      set_pixel(pixels, pitch, (top_left_x + i), (top_left_y + j), color);
    }
  }
}

void render(size_t frame_count, void *pixels, int pitch) {
  size_t x = frame_count * 20 % WIDTH;
  size_t y = (frame_count * 20 / WIDTH) * 20;

  // Create color that cycles through RGB based on frame count
  uint8_t r = (uint8_t)((256 * x / WIDTH) % 256);
  uint8_t g = (uint8_t)((256 * x / WIDTH) % 256);
  uint8_t b = (uint8_t)((256 * x / WIDTH) % 256);
  uint32_t color = 0xFF000000 | (r << 16) | (g << 8) | b;

  memset(V_PIXELS, 0, NUM_BYTES_IN_FRAMEBUFFER);
  draw_square(V_PIXELS, pitch, x, y, 20, color);
  memcpy(pixels, V_PIXELS, NUM_BYTES_IN_FRAMEBUFFER);
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

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT)
        running = 0;
    }

    void *pixels;
    int pitch;
    SDL_LockTexture(framebuffer, NULL, &pixels, &pitch);

    render(frame_count, pixels, pitch);

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