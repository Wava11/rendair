#include "physics/light.h"
#include "physics/transforms.h"
#include "physics/world.h"
#include "renders.h"
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

void render(size_t frame_count, struct Screen *screen, struct World *world,
            void *pixels) {
  clear_screen(screen);
  // render_running_square(screen, frame_count);
  // render_lines(screen, frame_count);
  // render_triangles(screen, frame_count);
  // render_circles(screen, frame_count);

  // rotate_hull(&world->hulls[1], 0.01);
  rotate_hull_around(&world->hulls[1], 0.01,
                     (struct Vec2){.x = 300., .y = 400.});
  rotate_hull_around(&world->hulls[0], 0.01,
                     (struct Vec2){.x = 200., .y = 300.});

  render_world(screen, world);
  render_point_light(screen, world, (struct Vec2){.x = 300., .y = 400.},
                     0xFFFFFFFF);
  memcpy(pixels, screen->pixels, NUM_BYTES_IN_FRAMEBUFFER);
}

int main(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("SDL_Init Error: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *window = get_window(WIDTH, HEIGHT);

  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_Texture *framebuffer =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                        SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

  int is_running = 1;
  int is_paused = 0;
  SDL_Event event;

  size_t frame_count = 0;
  struct Screen screen = {
      .pixels = V_PIXELS,
      .pitch = WIDTH * sizeof(uint32_t),
      .width = WIDTH,
      .height = HEIGHT,
  };

  struct World world;
  spawn_circle(&world, (struct Vec2){.x = 200., .y = 100.}, 50.);
  struct Vec2 vertices[] = {
      (struct Vec2){.x = 500., .y = 300.},
      (struct Vec2){.x = 400., .y = 300.},
      (struct Vec2){.x = 450., .y = 400.},
  };
  spawn_polygon(&world, vertices, 3);

  while (is_running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        is_running = 0;
      } else if (event.type == SDL_KEYDOWN &&
                 event.key.keysym.sym == SDLK_SPACE) {
        is_paused = !is_paused;
      }
    }

    void *pixels;
    int pitch;
    if (!is_paused) {
      SDL_LockTexture(framebuffer, NULL, &pixels, &pitch);

      render(frame_count, &screen, &world, pixels);
      frame_count++;

      SDL_UnlockTexture(framebuffer);
      SDL_RenderCopy(renderer, framebuffer, NULL, NULL);
      SDL_RenderPresent(renderer);
    } else {
      SDL_Delay(16);
    }
  }

  printf("Quitting...\n");
  SDL_DestroyTexture(framebuffer);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}