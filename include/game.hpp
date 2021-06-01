#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vec2f.hpp>
#include <car.hpp>
#include <image.hpp>

class game {
private:
  void init(SDL_Window*& window, SDL_Renderer*& renderer) const;
  float get_current_time() const { return SDL_GetTicks() / 1000.0f; }

public:
  void play() const;

};
