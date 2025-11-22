#ifndef LINALG_H
#define LINALG_H

struct Vec2 {
  float x;
  float y;
};

struct Vec2 rotate_around(struct Vec2 p, struct Vec2 center, float angle);
struct Vec2 add_vec(struct Vec2 p1, struct Vec2 p2);
struct Vec2 sub_vec(struct Vec2 p1, struct Vec2 p2);
struct Vec2 mul_scalar_vec(float scalar, struct Vec2 p);
float norm_vec(struct Vec2 p);

#endif