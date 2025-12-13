#include "velocity.h"
#include "transforms.h"
#include "world.h"

void apply_velocities(struct World *world) {
  for (size_t i = 0; i < world->entity_count; i++) {
    translate_entity(world, i, world->velocities[i]);
  }
}

void set_velocity(struct World *world, size_t entity_id, struct Vec2 velocity) {
  world->velocities[entity_id] = velocity;
}