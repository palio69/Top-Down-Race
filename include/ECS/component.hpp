#pragma once

#include <SDL2/SDL.h>
#include <utils.hpp>
#include <vec2f.hpp>
#include <picture.hpp>



struct input_keys {
  key up = KEY(UP),
    down = KEY(DOWN),
    left = KEY(LEFT),
    right = KEY(RIGHT),
    nitro = KEY(N),
    reset_pos = KEY(Z);
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
