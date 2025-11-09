#ifndef LINALG_H
#define LINALG_H

struct Vec2 {
  float x;
  float y;
};

struct Vec2 rotate_around(struct Vec2 p, struct Vec2 center, float angle);
#endif