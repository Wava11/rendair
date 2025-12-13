#ifndef CONTROLS_H
#define CONTROLS_H

#include "../physics/world.h"
#include <SDL.h>

void handle_player_movement(struct World *world);
void handle_player_fire(struct World *world, SDL_Event *event);


#endif