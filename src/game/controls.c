#include "controls.h"
#include "../physics/transforms.h"
#include "../physics/velocity.h"
#include "player.h"
#include <SDL.h>

void handle_player_movement(struct World *world) {
  const Uint8 *keys = SDL_GetKeyboardState(NULL);

  if (keys[SDL_SCANCODE_RIGHT]) {
    rotate_entity(world, PLAYER_ID, 0.02);
  }
  if (keys[SDL_SCANCODE_LEFT]) {
    rotate_entity(world, PLAYER_ID, -0.02);
  }
  if (keys[SDL_SCANCODE_UP]) {
    struct Vec2 direction = angle_to_direction(world->rotations[PLAYER_ID]);
    world->velocities[PLAYER_ID] = mul_scalar_vec(player_speed, direction);
  } else {
    if (norm_vec(world->velocities[PLAYER_ID]) > 0.1) {
      world->velocities[PLAYER_ID] =
          mul_scalar_vec(0.99, world->velocities[PLAYER_ID]);
    } else {
      world->velocities[PLAYER_ID] = (struct Vec2){.x = 0., .y = 0.};
    }
  }
}

#define BULLET_SPEED 5.
void handle_player_fire(struct World *world, SDL_Event *event) {
  if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_z &&
      !event->key.repeat) {
    size_t bullet_id = spawn_circle(world, get_player_gun_position(world), 5.);
    set_velocity(
        world, bullet_id,
        mul_scalar_vec(BULLET_SPEED,
                       angle_to_direction(world->rotations[PLAYER_ID])));
  }
}