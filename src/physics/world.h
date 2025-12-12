#ifndef WORLD_H
#define WORLD_H

#include "hulls.h"
#include <stddef.h>
#define MAX_ENTITIES 1000

struct World {
  size_t entity_count;
  struct Hull hulls[MAX_ENTITIES];
  struct Vec2 positions[MAX_ENTITIES];
  float rotations[MAX_ENTITIES];
  
  struct Vec2 velocities[MAX_ENTITIES];
};

void spawn_circle(struct World *world, struct Vec2 center, float radius);
void spawn_polygon(struct World *world, struct Vec2 vertices[MAX_VERTICES], size_t vertex_count);

#endif