#ifndef CONTROLS_H
#define CONTROLS_H

#include "../physics/world.h"
#include <SDL.h>

void handle_player_controls(struct World *world, SDL_Event *event);

#endif