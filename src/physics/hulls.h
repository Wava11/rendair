#ifndef HULLS_H
#define HULLS_H

#include "../linalg.h"
#include <stddef.h>
#define MAX_VERTICES 8

enum Type { POLYGON, CIRCLE };
union HullData {
  struct PolygonData {
    struct Vec2 vertices[MAX_VERTICES];
    size_t vertex_count;
  } polygon;

  struct CircleData {
    struct Vec2 center;
    float radius;
  } circle;
};

struct Hull {
  enum Type type;
  union HullData data;
};

struct ClosureBounds {
  struct Vec2 first;
  struct Vec2 second;
} ClosureBounds;

struct ClosureBounds get_closure_bounds(struct Hull *hull, struct Vec2 reference_point);
struct Vec2 get_hull_center(struct Hull *hull);

#endif
