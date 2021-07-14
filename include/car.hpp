#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <system.hpp>
#include <vec2f.hpp>
#include <picture.hpp>
#include <camera.hpp>
#include <map.hpp>

struct movement {
  float max_speed,
    acceleration,
    deceleration;
  double angle = 0.0;
};

class car {
private:
  const vec2f origin;
  vec2f pos;
  float speed,
    goal_speed,
    booster;
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
    speed(0.0f), goal_speed(0.0f),
    booster(1.0f),
    ent(ent),

    cam(cam),
    sprite(sprite) { }
  ~car() { }

  void update(const Uint8* key);

};
