#ifndef SHAPES_H
#define SHAPES_H

#include "screen.h"
#include <stddef.h>
#include <stdint.h>
#include "linalg.h"

void draw_square(struct Screen *screen, size_t top_left_x, size_t top_left_y,
                 size_t length, uint32_t color);

void draw_line(struct Screen *screen, struct Vec2 p1, struct Vec2 p2, uint32_t color);


#endif