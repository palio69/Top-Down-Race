#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <image.hpp>
#include <camera.hpp>
#include <map.hpp>

class car {
private:
  vec2f pos;
  float speed,
    goal_speed;
  const float max_speed;
  double angle;

  tile_map* current_map;
  camera& cam;

  image sprite;
  const SDL_RendererFlip flip;

  void update_data(
		   const Uint8* key,
		   float& booster, const double angle_modifier,
		   const vec2f origin
		   );
  void update_physics(
		      const float acceleration, const float deceleration,
		      const float friction, const float booster,
		      const float delta_time
		      );
  void update_sprite();

public:
  car(
      const vec2f pos,
      const float max_speed,
      const double angle,

      tile_map* current_map,
      camera& cam,

      const image sprite,
      const SDL_RendererFlip flip
      ) :
    pos(pos),
    speed(0.0f), goal_speed(0.0f), max_speed(max_speed),
    angle(angle),

    current_map(current_map),
    cam(cam),

    sprite(sprite),
    flip(flip) { }
  ~car() { SDL_DestroyTexture(this->sprite.tex); }

  vec2f get_pos() const { return this->pos; }

  void update(const Uint8* key, const float delta_time);
  void render(SDL_Renderer* renderer) const;

};
