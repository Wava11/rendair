#include "player.h"
#include "../physics/world.h"

size_t PLAYER_ID = -1;

void spawn_player(struct World *world) {
  struct Vec2 player_vertices[] = {(struct Vec2){.x = 450., .y = 292.5},
                                   (struct Vec2){.x = 462.5, .y = 317.5},
                                   (struct Vec2){.x = 450., .y = 309.},
                                   (struct Vec2){.x = 437.5, .y = 317.5}};
  spawn_polygon(world, player_vertices, 4);
  PLAYER_ID = world->entity_count - 1;
}