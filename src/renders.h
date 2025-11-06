#ifndef RENDERS_H
#define RENDERS_H

#include <SDL.h>
#include "screen.h"

#define set_pixel(screen, x, y, color)                                  \
  ((uint32_t *)((uint8_t *)screen->pixels + y * screen->pitch))[x] = color;

void render_running_square(size_t frame_count, struct Screen* screen);

void render_line(struct Screen* screen);

#endif
