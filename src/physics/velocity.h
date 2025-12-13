#ifndef VELOCITY_H
#define VELOCITY_H

#include "world.h"

void apply_velocities(struct World *world);
void set_velocity(struct World *world, size_t entity_id, struct Vec2 velocity);

#endif