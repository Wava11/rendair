#include "shapes.h"
#include "renders.h"
#include <stddef.h>

void draw_square(struct Screen *screen, size_t top_left_x, size_t top_left_y,
                 size_t length, uint32_t color) {
  for (size_t i = 0; i < length; i++) {
    for (size_t j = 0; j < length; j++) {
      set_pixel(screen, (top_left_x + i), (top_left_y + j), color);
    }
  }
}

void draw_line(struct Screen *screen, struct Point p1, struct Point p2,
               uint32_t color) {
  struct Point left = p1.x < p2.x ? p1 : p2;
  struct Point right = p1.x < p2.x ? p2 : p1;

  float incline = (float)(right.y - left.y) / (float)(right.x - left.x);

  size_t curr_x_length = 0;
  size_t y = left.y;
  for (size_t x = left.x; x <= right.x; x++) {
    set_pixel(screen, x, y, color);
    curr_x_length++;
    if ((float)curr_x_length >= fabs(incline)) {
      y++;
      curr_x_length = 0;
    }
  }
}
