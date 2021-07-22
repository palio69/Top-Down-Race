#pragma once

#include <vec2f.hpp>

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
