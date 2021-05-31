#pragma once

#include <SDL2/SDL.h>

struct image {
  SDL_Texture* tex;
  SDL_Rect src, des;

};
