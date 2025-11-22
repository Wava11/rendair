#include "../linalg.h"
#include "../screen.h"
#include "../shapes.h"
#include "hulls.h"
#include "world.h"
#include <stddef.h>
#include <stdint.h>

void render_point_light(struct Screen *screen, struct World *world,
                        struct Vec2 center, uint32_t color) {
  for (size_t i = 0; i < world->entity_count; i++) {
    struct Hull hull = world->hulls[i];
    struct ClosureBounds bounds = get_closure_bounds(&hull, center);

    draw_line(screen, center, bounds.first, color);
    draw_line(screen, center, bounds.second, color);
  }
}
