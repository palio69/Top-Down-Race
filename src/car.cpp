#include <car.hpp>



void car::update(const Uint8* key, const float delta_time) {
  auto to_radians = [] (const double angle) {
    const double pi = 3.141592654;
    return angle * pi / 180;
  };

  const float friction = 12.5f,
    acceleration = delta_time * friction,
    limiter = 0.05f;
  const double angle_modifier = 0.3;

  const bool up = key[SDL_SCANCODE_UP],
    down = key[SDL_SCANCODE_DOWN],
    left = key[SDL_SCANCODE_LEFT],
    right = key[SDL_SCANCODE_RIGHT],
    z = key[SDL_SCANCODE_Z],

    up_xor_down = ((up || down) && !(up && down));



  if (up_xor_down) {
    if (up)
      this->goal_speed = this->max_speed;

    if (down)
      this->goal_speed = this->max_speed / -4.0f;

  } else
    this->goal_speed = 0.0f;

  if (left)
    this->angle -= angle_modifier;

  if (right)
    this->angle += angle_modifier;

  if (z)
    this->pos = { 0.0f, 0.0f };



  if (this->speed < this->goal_speed)
    this->speed += acceleration;

  if (this->speed > this->goal_speed)
    this->speed -= acceleration;



  this->pos.x += speed * std::sin(to_radians(this->angle)) * limiter;
  this->pos.y -= speed * std::cos(to_radians(this->angle)) * limiter;

}

void car::render(SDL_Renderer* renderer) const {
  SDL_RenderCopyEx(renderer, this->sprite.tex, &(this->sprite.src), &(this->sprite.des), this->angle, nullptr, this->flip);
}
