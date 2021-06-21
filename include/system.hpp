#pragma once

#include <SDL2/SDL.h>

class time_system {
private:
  time_system() { }
  ~time_system() { }

  static float current_time,
    next_time,
    delta_time;

public:
  static float get_delta_time() { return delta_time; }
  static float get_current_time() { return SDL_GetTicks() / 1000.0f; }

  static void init();
  static void work();

};
