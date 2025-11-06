#ifndef SCREEN_H
#define SCREEN_H

#include <stddef.h>
struct Screen {
  void *pixels;
  int pitch;
  size_t width;
  size_t height;
};

#endif