#include "linalg.h"
#include <math.h>
struct Vec2 rotate_around(struct Vec2 p, struct Vec2 center, float angle) {
  struct Vec2 translated = {.x = p.x - center.x, .y = p.y - center.y};
  struct Vec2 rotated = {
      .x = translated.x * cosf(angle) - translated.y * sinf(angle),
      .y = translated.x * sinf(angle) + translated.y * cosf(angle)};
  return (struct Vec2){.x = rotated.x + center.x, .y = rotated.y + center.y};
}