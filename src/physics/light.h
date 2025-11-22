#ifndef LIGHT_H
#define LIGHT_H

#include "../linalg.h"
#include "world.h"
#include <stddef.h>
#include <stdint.h>

void render_point_light(struct Screen *screen, struct World *world,
                        struct Vec2 center, uint32_t color);

#endif