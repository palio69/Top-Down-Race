#pragma once

#include <SDL2/SDL.h>

struct picture {
  SDL_Rect src = { 0, 0, 0, 0 },
    des = { 0, 0, 0, 0 };
  double angle = 0.0;
  SDL_Point* center = nullptr;
  SDL_RendererFlip flip = SDL_FLIP_NONE;

};
