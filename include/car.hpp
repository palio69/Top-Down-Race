#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <system.hpp>
#include <vec2f.hpp>
#include <picture.hpp>
#include <camera.hpp>
#include <map.hpp>

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

class car {
private:
  const ECS::entity ent;
  camera& cam;
  picture sprite;

  void update_data();
  void update_physics(const float friction);
  void update_sprite();

public:
  car(const ECS::entity ent, camera& cam, const picture sprite) :
    ent(ent), cam(cam), sprite(sprite) { }
  ~car() { }

  void update();

};
