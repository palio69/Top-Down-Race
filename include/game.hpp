#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <system.hpp>
#include <vec2f.hpp>
#include <image.hpp>
#include <map.hpp>
#include <car.hpp>

class game {
private:
  static void init(SDL_Window*& window, SDL_Renderer*& renderer);

public:
  static void play();

};
