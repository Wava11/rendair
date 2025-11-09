#ifndef RENDERS_H
#define RENDERS_H

#include "screen.h"
#include <SDL.h>

#define set_pixel(screen, x, y, color)                                         \
  ((uint32_t *)((uint8_t *)screen->pixels + y * screen->pitch))[x] = color;

void render_running_square(struct Screen *screen, size_t frame_count);

void render_lines(struct Screen *screen, size_t frame_count);

#endif
