#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <system.hpp>
#include <vec2f.hpp>
#include <picture.hpp>
#include <map.hpp>
#include <car.hpp>

class game {
private:
  static bool init_dependencies();
  static bool init_objs();
  static void init_systems();

  static void init();

public:
  static void play();

};
