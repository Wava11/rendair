#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "hulls.h"

void translate_hull(struct Hull *hull, struct Vec2 translation);
void rotate_hull(struct Hull *hull, float angle);
void rotate_hull_around(struct Hull *hull, float angle, struct Vec2 center);
void scale_hull(struct Hull *hull, float scale);

#endif