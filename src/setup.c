#include <SDL.h>

SDL_Window *get_window(int width, int height) {
  int num_displays = SDL_GetNumVideoDisplays();
  SDL_Log("Number of displays: %d", num_displays);

  int display_index =
      2; // Change this to select a different display (0 = primary)
  if (display_index >= num_displays) {
    display_index = 0;
  }

  SDL_Rect display_bounds;
  SDL_GetDisplayBounds(display_index, &display_bounds);
  SDL_Log("Using display %d at position (%d, %d)", display_index,
          display_bounds.x, display_bounds.y);

  // Position window on the chosen display
  int window_x = display_bounds.x + (display_bounds.w - width) / 2;
  int window_y = display_bounds.y + (display_bounds.h - height) / 2;

  SDL_Window *window =
      SDL_CreateWindow("rendair", window_x, window_y, width, height, 0);
  return window;
}