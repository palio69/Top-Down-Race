#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <image.hpp>
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
  image sprite;
  const SDL_RendererFlip flip;

  void update_data(const Uint8* key, const double angle_modifier);
  void update_physics(const float friction, const float delta_time);
  void update_sprite();

public:
  car(
      const vec2f origin,
      const float max_speed,
      const float acceleration, const float deceleration,
      const double angle,

      camera& cam,
      const image sprite,
      const SDL_RendererFlip flip
      ) :
    origin(origin), pos(origin),
    speed(0.0f), goal_speed(0.0f),
    booster(1.0f),
    max_speed(max_speed),
    acceleration(acceleration), deceleration(deceleration),
    angle(angle),

    cam(cam),
    sprite(sprite),
    flip(flip) { }
  ~car() { SDL_DestroyTexture(this->sprite.tex); }

  void update(const Uint8* key, const float delta_time);
  void render(SDL_Renderer* renderer) const;

};
