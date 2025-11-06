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
  struct Vec2 left = p1.x < p2.x ? p1 : p2;
  struct Vec2 right = p1.x < p2.x ? p2 : p1;

  float incline = (right.y - left.y) / (right.x - left.x);
  printf("%f\n", incline);


  for (float x = left.x; x <= right.x; x++) {
   float y =  incline * (x - left.x) + left.y;
   set_pixel(screen, (size_t)x, (size_t)y, color);
  }
}
