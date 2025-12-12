#include "linalg.h"
#include <math.h>

struct Vec2 angle_to_direction(float angle) {
  return (struct Vec2){.x = cosf(angle), .y = sinf(angle)};
}

struct Vec2 rotate_around(struct Vec2 p, struct Vec2 center, float angle) {
  struct Vec2 translated = {.x = p.x - center.x, .y = p.y - center.y};
  struct Vec2 rotated = {
      .x = translated.x * cosf(angle) - translated.y * sinf(angle),
      .y = translated.x * sinf(angle) + translated.y * cosf(angle)};
  return (struct Vec2){.x = rotated.x + center.x, .y = rotated.y + center.y};
}

struct Vec2 add_vec(struct Vec2 p1, struct Vec2 p2) {
  return (struct Vec2){.x = p1.x + p2.x, .y = p1.y + p2.y};
}

struct Vec2 sub_vec(struct Vec2 p1, struct Vec2 p2) {
  return (struct Vec2){.x = p1.x - p2.x, .y = p1.y - p2.y};
}

struct Vec2 mul_scalar_vec(float scalar, struct Vec2 p) {
  return (struct Vec2){.x = p.x * scalar, .y = p.y * scalar};
}

float norm_vec(struct Vec2 p) { return sqrtf(p.x * p.x + p.y * p.y); }

void translate_vecs(struct Vec2 *p, size_t count, struct Vec2 translation) {
  for (size_t i = 0; i < count; i++) {
    p[i] = add_vec(p[i], translation);
  }
}


struct Vec2 calculate_center(struct Vec2 *vertices, size_t vertex_count) {
  // Calculate true centroid (center of mass) using the shoelace formula
  float area = 0.0f;
  struct Vec2 centroid = {.x = 0.0f, .y = 0.0f};

  for (size_t i = 0; i < vertex_count; i++) {
    size_t j = (i + 1) % vertex_count;
    struct Vec2 vi = vertices[i];
    struct Vec2 vj = vertices[j];

    float cross = vi.x * vj.y - vj.x * vi.y;
    area += cross;
    centroid.x += (vi.x + vj.x) * cross;
    centroid.y += (vi.y + vj.y) * cross;
  }

  area *= 0.5f;
  centroid.x /= (6.0f * area);
  centroid.y /= (6.0f * area);
  return centroid;
}


void rotate_vecs(struct Vec2 *p, size_t count, float angle) {
  struct Vec2 center = calculate_center(p, count);
  for (size_t i = 0; i < count; i++) {
    p[i] = rotate_around(p[i], center, angle);
  }
}