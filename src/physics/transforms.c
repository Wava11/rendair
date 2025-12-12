#include "transforms.h"
#include "../linalg.h"
#include "hulls.h"
#include <stdio.h>
#include <stdlib.h>

void translate_hull(struct Hull *hull, struct Vec2 translation) {
  if (hull->type == POLYGON) {
    for (size_t i = 0; i < hull->data.polygon.vertex_count; i++) {
      hull->data.polygon.vertices[i] =
          add_vec(hull->data.polygon.vertices[i], translation);
    }
  } else if (hull->type == CIRCLE) {
    hull->data.circle.center = add_vec(hull->data.circle.center, translation);
  } else {
    perror("Hull has undefined type");
    abort();
  }
}

void rotate_hull(struct Hull *hull, float angle) {
  if (hull->type == POLYGON) {
    struct Vec2 center = get_hull_center(hull);
    for (size_t i = 0; i < hull->data.polygon.vertex_count; i++) {
      hull->data.polygon.vertices[i] =
          rotate_around(hull->data.polygon.vertices[i], center, angle);
    }
  }
}

void rotate_hull_around(struct Hull *hull, float angle, struct Vec2 center) {
  if (hull->type == POLYGON) {
    for (size_t i = 0; i < hull->data.polygon.vertex_count; i++) {
      hull->data.polygon.vertices[i] =
          rotate_around(hull->data.polygon.vertices[i], center, angle);
    }
  } else if (hull->type == CIRCLE) {
    hull->data.circle.center =
        rotate_around(hull->data.circle.center, center, angle);
  } else {
    perror("Hull has undefined type");
    abort();
  }
}

void scale_hull(struct Hull *hull, float scale) {
  if (hull->type == POLYGON) {
    struct Vec2 center = get_hull_center(hull);
    for (size_t i = 0; i < hull->data.polygon.vertex_count; i++) {
      struct Vec2 v = hull->data.polygon.vertices[i];
      struct Vec2 offset = sub_vec(v, center);
      struct Vec2 scaled_offset = mul_scalar_vec(scale, offset);
      hull->data.polygon.vertices[i] = add_vec(center, scaled_offset);
    }
  } else if (hull->type == CIRCLE) {
    hull->data.circle.radius *= scale;
  } else {
    perror("Hull has undefined type");
    abort();
  }
}

void translate_entity(struct World *world, size_t entity_id,
                      struct Vec2 translation) {
  world->positions[entity_id] =
      add_vec(world->positions[entity_id], translation);
}
void rotate_entity(struct World *world, size_t entity_id, float angle) {
  world->rotations[entity_id] += angle;
}