#ifndef SHAPES_H
#define SHAPES_H

#include "screen.h"
#include <stddef.h>
#include <stdint.h>

struct Point {
  size_t x;
  size_t y;
};

void draw_square(struct Screen *screen, size_t top_left_x, size_t top_left_y,
                 size_t length, uint32_t color);

void draw_line(struct Screen *screen, struct Point p1, struct Point p2, uint32_t color);

#endif