#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "hulls.h"
#include "world.h"

void translate_hull(struct Hull *hull, struct Vec2 translation);
void rotate_hull(struct Hull *hull, float angle);
void rotate_hull_around(struct Hull *hull, float angle, struct Vec2 center);
void scale_hull(struct Hull *hull, float scale);

void translate_entity(struct World *world, size_t entity_id, struct Vec2 translation);
void rotate_entity(struct World *world, size_t entity_id, float angle);

#endif