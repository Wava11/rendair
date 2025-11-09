#include "renders.h"
#include "linalg.h"
#include "shapes.h"
#include <stdlib.h>

void render_running_square(struct Screen *screen, size_t frame_count) {
  size_t x = frame_count * 20 % screen->width;
  size_t y = (frame_count * 20 / screen->width) * 20;

  // Create color that cycles through RGB based on frame count
  uint8_t r = (uint8_t)((256 * x / screen->width) % 256);
  uint8_t g = (uint8_t)((256 * x / screen->width) % 256);
  uint8_t b = (uint8_t)((256 * x / screen->width) % 256);
  uint32_t color = 0xFF000000 | (r << 16) | (g << 8) | b;

  memset(screen->pixels, 0, screen->width * screen->height * sizeof(uint32_t));
  draw_square(screen, x, y, 20, color);
}

struct Vec2 generate_random_vec(struct Screen *screen) {
  struct Vec2 p;
  p.x = (float)(rand() % screen->width);
  p.y = (float)(rand() % screen->height);
  return p;
}

void render_lines(struct Screen *screen, size_t frame_count) {
  memset(screen->pixels, 0, screen->width * screen->height * sizeof(uint32_t));

  float rotation_speed1 = 0.1;
  struct Vec2 c = {.x = 400., .y = 300.};
  struct Vec2 p1 = {.x = 100., .y = 540.};
  p1 = rotate_around(p1, c, frame_count * rotation_speed1);
  struct Vec2 p2 = {.x = 400., .y = 100.};
  p2 = rotate_around(p2, c, frame_count * rotation_speed1);
  draw_line(screen, p1, p2, 0xFFFFFFFF);

  float rotation_speed2 = 0.01;
  struct Vec2 c2 = {.x = 300., .y = 300.};
  struct Vec2 p12 = {.x = 200., .y = 200.};
  p12 = rotate_around(p12, c2, frame_count * rotation_speed2);
  struct Vec2 p22 = {.x = 400., .y = 400.};
  p22 = rotate_around(p22, c2, frame_count * rotation_speed2);
  draw_line(screen, p12, p22, 0xFFFFFFFF);

  draw_line(screen,
            (struct Vec2){.x = (50 + frame_count*3) % screen->width, .y = 50},
            (struct Vec2){.x = (50 + frame_count*3) % screen->width, .y = 350},
            0xFFFFFFFF);

  //   for (int i = 0; i < 2000; i++) {
  //     struct Vec2 p1 = generate_random_vec(screen);
  //     struct Vec2 p2 = generate_random_vec(screen);
  //     draw_line(screen, p1, p2, 0xFFFFFFFF);
  //   }
}
