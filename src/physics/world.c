#include "world.h"
#include "hulls.h"

void spawn_circle(struct World *world, struct Vec2 center, float radius) {
  struct Hull circle = {
      .type = CIRCLE, .data = {.circle = {.center = center, .radius = radius}}};
  world->hulls[world->entity_count] = circle;
  world->entity_count++;
}

void spawn_polygon(struct World *world, struct Vec2 vertices[MAX_VERTICES],
                   size_t vertex_count) {
  struct Hull polygon = {.type = POLYGON,
                         .data = {.polygon = {.vertex_count = vertex_count}}};
  
  for (size_t i = 0; i < vertex_count; i++) {
    polygon.data.polygon.vertices[i] = vertices[i];
  }
  
  world->hulls[world->entity_count] = polygon;
  world->entity_count++;
}