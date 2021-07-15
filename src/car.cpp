#include <car.hpp>



void car::update() {
  const float friction = 1.05f;
  this->update_data();
  this->update_physics(friction);
  this->update_sprite();

}

void car::update_data() {
  auto data = *(ECS::component<movement>(this->ent));
  auto& goal_speed = data.goal_speed;
  auto& booster = data.booster;
  auto& angle = data.angle;
  const auto max_speed = data.max_speed;
  const auto turn_speed = data.turn_speed;

  const Uint8* key = event_system::key();
  const auto delta_time = time_system::delta_time();

  const bool up = key[SDL_SCANCODE_UP],
    down = key[SDL_SCANCODE_DOWN],
    left = key[SDL_SCANCODE_LEFT],
    right = key[SDL_SCANCODE_RIGHT],

    n = key[SDL_SCANCODE_N],
    z = key[SDL_SCANCODE_Z],

    up_xor_down = ((up || down) && !(up && down));



  if (n)
    booster = 1.75f;

  else
    booster = 1.0f;

  if (up_xor_down) {
    if (up)
      goal_speed = max_speed * booster;

    if (down)
      goal_speed = max_speed / -4.0f;

  } else
    goal_speed = 0.0f;

  if (left)
    angle -= turn_speed * delta_time;

  if (right)
    angle += turn_speed * delta_time;

  if (z)
    this->pos = this->origin;

  ECS::component<movement>(this->ent, data);
}

void car::update_physics(const float friction) {
  auto data = *(ECS::component<movement>(this->ent));
  auto& speed = data.speed;
  const auto goal_speed = data.goal_speed;
  const auto acceleration = data.acceleration;
  const auto deceleration = data.deceleration;
  const auto booster = data.booster;
  const auto angle = data.angle;

  const auto delta_time = time_system::delta_time();

  auto to_radians = [] (const double angle) {
    const double pi = 3.141592654;
    return angle * pi / 180;
  };

  const float final_acceleration = acceleration * delta_time * friction * booster,
    final_deceleration = deceleration * delta_time * friction * booster,

    x_side = std::sin(to_radians(angle)),
    y_side = std::cos(to_radians(angle));
  const vec2f sides = { x_side, -y_side };
  vec2f final_pos = sides * delta_time;



  if (speed < goal_speed)
    speed += final_acceleration;

  if (speed > goal_speed)
    speed -= final_deceleration;



  final_pos *= speed;
  this->pos += final_pos;

  this->cam.update(this->pos);

  ECS::component<movement>(this->ent, data);
}

void car::update_sprite() {
  auto data = *(ECS::component<movement>(this->ent));
  const auto angle = data.angle;

  this->sprite.des.x = this->pos.x - this->cam.get_camera_pos().x;
  this->sprite.des.y = this->pos.y - this->cam.get_camera_pos().y;
  this->sprite.angle = angle;
  texture_system::add_texture(this->sprite);
}
