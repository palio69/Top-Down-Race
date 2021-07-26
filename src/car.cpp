#include <car.hpp>



void car::update() {
  const float friction = 1.05f;
  auto sprt = *(ECS::component<sprite>(this->ent));
  auto pstn = *(ECS::component<position>(this->ent));
  auto move = *(ECS::component<movement>(this->ent));

  auto& spr = sprt.spr;
  auto& pos = pstn.pos;
  auto& angle = pstn.angle;
  auto& speed = move.speed;
  auto& goal_speed = move.goal_speed;
  auto& booster = move.booster;
  const auto origin = pstn.origin;
  const auto max_speed = move.max_speed;
  const auto acceleration = move.acceleration;
  const auto deceleration = move.deceleration;
  const auto turn_speed = move.turn_speed;

  const Uint8* key = event_system::key();
  const auto delta_time = time_system::delta_time();

  const bool up = key[SDL_SCANCODE_UP],
    down = key[SDL_SCANCODE_DOWN],
    left = key[SDL_SCANCODE_LEFT],
    right = key[SDL_SCANCODE_RIGHT],

    n = key[SDL_SCANCODE_N],
    z = key[SDL_SCANCODE_Z],

    up_xor_down = ((up || down) && !(up && down));

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
    pos = origin;



  if (speed < goal_speed)
    speed += final_acceleration;

  if (speed > goal_speed)
    speed -= final_deceleration;

  final_pos *= speed;
  pos += final_pos;

  this->cam.update(pos);



  spr.des.x = pos.x - this->cam.get_camera_pos().x;
  spr.des.y = pos.y - this->cam.get_camera_pos().y;
  spr.angle = angle;
  picture_system::add_picture(spr);



  ECS::component(this->ent, sprt);
  ECS::component(this->ent, pstn);
  ECS::component(this->ent, move);
}
