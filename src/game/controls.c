#include "controls.h"
#include "../physics/transforms.h"
#include "player.h"
#include <SDL.h>

void handle_player_controls(struct World *world, SDL_Event *event) {
  const Uint8 *keys = SDL_GetKeyboardState(NULL);
  
  if (keys[SDL_SCANCODE_RIGHT]) {
    rotate_hull(&world->hulls[PLAYER_ID], 0.02);
  }
  if (keys[SDL_SCANCODE_LEFT]) {
    rotate_hull(&world->hulls[PLAYER_ID], -0.02);
  }
}