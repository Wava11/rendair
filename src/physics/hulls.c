#include "hulls.h"
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct ClosureBounds get_closure_bounds(struct Hull *hull,
                                        struct Vec2 reference_point) {
  struct ClosureBounds bounds;
  if (hull->type == POLYGON) {
    float min_incline = INFINITY;
    float max_incline = -INFINITY;
    for (size_t i = 0; i < hull->data.polygon.vertex_count; i++) {
      struct Vec2 v = hull->data.polygon.vertices[i];
      float incline = (v.y - reference_point.y) / (v.x - reference_point.x);
      if (incline < min_incline) {
        min_incline = incline;
        bounds.first = v;
      }
      if (incline > max_incline) {
        max_incline = incline;
        bounds.second = v;
      }
    }
  }

  else if (hull->type == CIRCLE) {
    struct CircleData circle = hull->data.circle;
    struct Vec2 v = sub_vec(reference_point, circle.center);
    float v_norm = norm_vec(v);
    struct Vec2 v_orthogonal = {.x = -v.y, .y = v.x};

    struct Vec2 a = circle.center;
    struct Vec2 b =
        mul_scalar_vec(circle.radius * circle.radius / (v_norm * v_norm), v);
    struct Vec2 c = mul_scalar_vec(
        circle.radius *
            (sqrtf(v_norm * v_norm - circle.radius * circle.radius)) /
            (v_norm * v_norm),
        v_orthogonal);

    bounds.first = add_vec(add_vec(a, b), c);
    bounds.second = sub_vec(add_vec(a, b), c);

  } else {
    perror("Hull has undefined type");
    abort();
  }

  return bounds;
}


struct Vec2 get_hull_center(struct Hull *hull) {
    if (hull->type == POLYGON) {
        // Calculate true centroid (center of mass) using the shoelace formula
        float area = 0.0f;
        struct Vec2 centroid = {.x = 0.0f, .y = 0.0f};
        
        for (size_t i = 0; i < hull->data.polygon.vertex_count; i++) {
            size_t j = (i + 1) % hull->data.polygon.vertex_count;
            struct Vec2 vi = hull->data.polygon.vertices[i];
            struct Vec2 vj = hull->data.polygon.vertices[j];
            
            float cross = vi.x * vj.y - vj.x * vi.y;
            area += cross;
            centroid.x += (vi.x + vj.x) * cross;
            centroid.y += (vi.y + vj.y) * cross;
        }
        
        area *= 0.5f;
        centroid.x /= (6.0f * area);
        centroid.y /= (6.0f * area);
        return centroid;
    } else if (hull->type == CIRCLE) {
        return hull->data.circle.center;
    } else {
        perror("Hull has undefined type");
        abort();
    }
}


