#include "controls.h"
#include "../physics/transforms.h"
#include "player.h"
#include <SDL.h>

void handle_player_controls(struct World *world, SDL_Event *event) {
  const Uint8 *keys = SDL_GetKeyboardState(NULL);
  
  if (keys[SDL_SCANCODE_RIGHT]) {
    rotate_entity(world, PLAYER_ID, 0.02);
  }
  if (keys[SDL_SCANCODE_LEFT]) {
    rotate_entity(world, PLAYER_ID, -0.02);
  }
  if(keys[SDL_SCANCODE_UP]){
    struct Vec2 direction = angle_to_direction(world->rotations[PLAYER_ID]);
    world->velocities[PLAYER_ID] =  mul_scalar_vec(player_speed, direction);
  } else {
    printf("%f\n", norm_vec(world->velocities[PLAYER_ID]));
    if (norm_vec(world->velocities[PLAYER_ID]) > 0.1) {
      world->velocities[PLAYER_ID] = mul_scalar_vec(0.99, world->velocities[PLAYER_ID]);
    } else {
      world->velocities[PLAYER_ID] = (struct Vec2){.x = 0., .y = 0.};
    }
  }
}