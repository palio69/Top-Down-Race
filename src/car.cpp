#include <car.hpp>



void car::update(const Uint8* key, const float delta_time) {
  auto to_radians = [] (const double angle) {
    const double pi = 3.141592654;
    return angle * pi / 180;
  };

  const float friction = 12.5f;

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
    this->angle -= 0.3;

  if (right)
    this->angle += 0.3;

  if (z)
    this->pos = { 0.0f, 0.0f };



  if (this->speed < this->goal_speed)
    this->speed += delta_time * friction;

  if (this->speed > this->goal_speed)
    this->speed -= delta_time * friction;



  this->pos.x += speed * std::sin(to_radians(this->angle)) * 0.05;
  this->pos.y -= speed * std::cos(to_radians(this->angle)) * 0.05;



  this->sprite.des.x = this->pos.x;
  this->sprite.des.y = this->pos.y;

}

void car::render(SDL_Renderer* renderer) const {
  SDL_RenderCopyEx(renderer, this->sprite.tex, &(this->sprite.src), &(this->sprite.des), this->angle, nullptr, this->flip);
}
