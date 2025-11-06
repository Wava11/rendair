#include "renders.h"
#include "shapes.h"
#include "linalg.h"

void render_running_square(size_t frame_count, struct Screen *screen) {
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

void render_line(struct Screen *screen) {
    struct Vec2 p1 = { .x = 100., .y = 540. };
    struct Vec2 p2 = { .x = 400., .y = 100. };
    draw_line(screen, p1, p2, 0xFFFFFFFF);
}