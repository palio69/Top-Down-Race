#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <system.hpp>
#include <vec2f.hpp>
#include <picture.hpp>
#include <camera.hpp>
#include <map.hpp>

struct movement {
  float speed,
    goal_speed,
    max_speed,

    acceleration,
    deceleration,
    booster;

  double angle = 0.0;
};

class car {
private:
  const vec2f origin;
  vec2f pos;
  const ECS::entity ent;
  camera& cam;
  picture sprite;

  void update_data(const Uint8* key, const double angle_modifier);
  void update_physics(const float friction);
  void update_sprite();

public:
  car(
      const vec2f origin,
      const ECS::entity ent,
      camera& cam,
      const picture sprite
      ) :
    origin(origin), pos(origin),
    ent(ent),
    cam(cam),
    sprite(sprite) { }
  ~car() { }

  void update(const Uint8* key);

};
