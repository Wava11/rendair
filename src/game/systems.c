#include "systems.h"
#include "../physics/velocity.h"

void apply_systems(struct World *world) {
  apply_velocities(world);
}