#include "player.h"
#include "../physics/transforms.h"
#include "../physics/world.h"
#include <math.h>

size_t PLAYER_ID = -1;
float player_speed = 2.;

struct Vec2 player_vertices[] = {
    (struct Vec2){.x = 25., .y = 12.5}, (struct Vec2){.x = 0., .y = 25.},
    (struct Vec2){.x = 8.5, .y = 12.5}, (struct Vec2){.x = 0., .y = 0.}};

void spawn_player(struct World *world) {
  spawn_polygon(world, player_vertices, 4);
  PLAYER_ID = world->entity_count - 1;
  translate_entity(world, PLAYER_ID, (struct Vec2){.x = 400., .y = 300.});
  rotate_entity(world, PLAYER_ID, -M_PI / 2);
}

struct Vec2 get_player_gun_position(struct World *world) {
  return get_positioned_hull(world, PLAYER_ID).data.polygon.vertices[0];
}