#include "world.h"
#include "hulls.h"

/**
 * returns the entity id
 */
size_t spawn_hull(struct World *world, struct Hull hull) {
  world->hulls[world->entity_count] = hull;
  return world->entity_count++;
}

size_t spawn_circle(struct World *world, struct Vec2 center, float radius) {
  struct Hull circle = {
      .type = CIRCLE, .data = {.circle = {.center = center, .radius = radius}}};
  return spawn_hull(world, circle);
}

size_t spawn_polygon(struct World *world, struct Vec2 vertices[MAX_VERTICES],
                     size_t vertex_count) {
  struct Hull polygon = {.type = POLYGON,
                         .data = {.polygon = {.vertex_count = vertex_count}}};

  for (size_t i = 0; i < vertex_count; i++) {
    polygon.data.polygon.vertices[i] = vertices[i];
  }

  return spawn_hull(world, polygon);
}

struct Hull get_positioned_hull(struct World *world, size_t entity_id) {
  struct Hull hull = world->hulls[entity_id];
  if (hull.type == CIRCLE) {
    hull.data.circle.center =
        add_vec(world->positions[entity_id], hull.data.circle.center);
  } else if (hull.type == POLYGON) {
    translate_vecs(hull.data.polygon.vertices, hull.data.polygon.vertex_count,
                   world->positions[entity_id]);
    rotate_vecs(hull.data.polygon.vertices, hull.data.polygon.vertex_count,
                world->rotations[entity_id]);
  }
  return hull;
}