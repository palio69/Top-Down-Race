#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <image.hpp>
#include <camera.hpp>

class car {
private:
  vec2f pos;
  float speed,
    goal_speed;
  const float max_speed;
  double angle;
  camera cam;

  image sprite;
  const SDL_RendererFlip flip;

public:
  car(
      const vec2f pos,
      const float max_speed,
      const double angle,

      const image sprite,
      const SDL_RendererFlip flip
      ) :
    pos(pos),
    speed(0.0f), goal_speed(0.0f), max_speed(max_speed),
    angle(angle),
    cam(pos),

    sprite(sprite),
    flip(flip) { }
  ~car() { SDL_DestroyTexture(this->sprite.tex); }

  camera get_cam() const { return this->cam; }

  void update(const Uint8* key, const float delta_time);
  void render(SDL_Renderer* renderer) const;

};
