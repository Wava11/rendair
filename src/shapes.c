#include "shapes.h"
#include "linalg.h"
#include "renders.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

void draw_square(struct Screen *screen, size_t top_left_x, size_t top_left_y,
                 size_t length, uint32_t color) {
  for (size_t i = 0; i < length; i++) {
    for (size_t j = 0; j < length; j++) {
      set_pixel(screen, (top_left_x + i), (top_left_y + j), color);
    }
  }
}

void draw_line(struct Screen *screen, struct Vec2 p1, struct Vec2 p2,
               uint32_t color) {
  if (p1.x == p2.x) {
    for (float y = p1.y; y <= p2.y; y++) {
      set_pixel(screen, (size_t)p1.x, (size_t)y, color);
    }
    return;
  }

  struct Vec2 left = p1.x < p2.x ? p1 : p2;
  struct Vec2 right = p1.x < p2.x ? p2 : p1;
  float max_y = fmax(p1.y, p2.y);
  float min_y = fmin(p1.y, p2.y);

  float incline = (right.y - left.y) / (right.x - left.x);
  float y_steps = floorf((max_y - min_y) / (right.x - left.x));
  for (float x = left.x; x <= right.x && x < screen->width; x++) {
    float y = incline * (x - left.x) + left.y;
    set_pixel(screen, (size_t)x, (size_t)y, color);

    float y_start = y;
    while (y < y_start + y_steps && y < max_y) {
      y++;
      set_pixel(screen, (size_t)x, (size_t)y, color);
    }
  }
}

void draw_triangle(struct Screen *screen, struct Vec2 p1, struct Vec2 p2,
                   struct Vec2 p3, uint32_t color) {
  draw_line(screen, p1, p2, color);
  draw_line(screen, p2, p3, color);
  draw_line(screen, p3, p1, color);
}