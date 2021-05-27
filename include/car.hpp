#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <vec2f.hpp>

class car {
private:
  vec2f pos;
  float speed,
    goal_speed,
    max_speed;
  double angle;

  SDL_Texture* sprite;
  SDL_Rect src, des;
  const SDL_RendererFlip flip;

public:
  car(
      const vec2f pos,
      const float speed, const float max_speed,
      const double angle,

      SDL_Texture* sprite,
      const SDL_Rect src, const SDL_Rect des,
      const SDL_RendererFlip flip
      ) :
    pos(pos),
    speed(speed), goal_speed(0.0f), max_speed(max_speed),
    angle(angle),

    sprite(nullptr),
    src(src), des(des),
    flip(flip) {
    this->sprite = sprite;
  }
  ~car() { SDL_DestroyTexture(this->sprite); }

  void update(const Uint8* key, const float delta_time);
  void render(SDL_Renderer* renderer) const;

};
