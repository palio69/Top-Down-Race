#pragma once

#include <SDL2/SDL.h>

struct image {
  SDL_Texture* tex;
  SDL_Rect src, des;

};

struct image_ex : image {
  double angle;
  SDL_Point* center;
  SDL_RendererFlip flip;

};
