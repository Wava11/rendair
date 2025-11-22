#include "linalg.h"
#include <math.h>
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

struct Vec2 mul_scalar_vec(float scalar, struct Vec2 p){
  return (struct Vec2){.x = p.x * scalar, .y = p.y * scalar};
}

float norm_vec(struct Vec2 p) {
  return sqrtf(p.x * p.x + p.y * p.y);
}


