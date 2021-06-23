#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <system.hpp>
#include <vec2f.hpp>
#include <picture.hpp>
#include <camera.hpp>
#include <map.hpp>

class car {
private:
  const vec2f origin;
  vec2f pos;
  float speed,
    goal_speed,
    booster;
  const float max_speed,
    acceleration,
    deceleration;
  double angle;

  camera& cam;
  picture sprite;

  void update_data(const Uint8* key, const double angle_modifier);
  void update_physics(const float friction);
  void update_sprite();

public:
  car(
      const vec2f origin,
      const float max_speed,
      const float acceleration, const float deceleration,
      const double angle,

      camera& cam,
      const picture sprite
      ) :
    origin(origin), pos(origin),
    speed(0.0f), goal_speed(0.0f),
    booster(1.0f),
    max_speed(max_speed),
    acceleration(acceleration), deceleration(deceleration),
    angle(angle),

    cam(cam),
    sprite(sprite) { }
  ~car() { }

  void update(const Uint8* key);
  void render() const { render_system::render(this->sprite); }

};
