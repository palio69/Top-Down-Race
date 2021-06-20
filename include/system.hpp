#pragma once

#include <SDL2/SDL.h>

namespace time_system {

#ifndef INTERN
  extern
#endif
  float current_time,
    next_time,
    delta_time;
  inline float get_current_time() { return SDL_GetTicks() / 1000.0f; }

  void init();
  void work();

}
