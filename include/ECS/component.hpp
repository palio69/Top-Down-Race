#pragma once

#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <picture.hpp>



struct input_keys {
  SDL_Scancode up = SDL_SCANCODE_UP,
    down = SDL_SCANCODE_DOWN,
    left = SDL_SCANCODE_LEFT,
    right = SDL_SCANCODE_RIGHT,
    nitro = SDL_SCANCODE_N,
    origin = SDL_SCANCODE_Z;
};

struct sprite {
  picture spr;
  int rows = 0, columns = 0,
    index = 0;
};

struct position {
  const vec2f origin;
  vec2f pos;
  double angle;

  constexpr position& operator =(const position obj) {
    this->pos = obj.pos;
    this->angle = obj.angle;
    return *this;
  }

};

struct movement {
  float speed,
    goal_speed,
    max_speed,

    acceleration,
    deceleration,
    booster;

  double turn_speed;
};
