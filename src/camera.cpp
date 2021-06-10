#include <camera.hpp>

void camera::update(const vec2f new_ref) {
  const vec2f refs_distance = new_ref - this->ref_pos,
    new_camera_pos = this->camera_pos + refs_distance,
    new_camera_wh = new_camera_pos + this->window_wh,

    xy2_limit = this->xy_limit + this->wh_limit,
    xy2_distance = xy2_limit - this->window_wh;

  vec2f final_camera_pos = new_camera_pos;



  if (new_camera_pos.x < this->xy_limit.x)
    final_camera_pos.x = this->xy_limit.x;

  else if (new_camera_wh.x > xy2_limit.x)
    final_camera_pos.x = xy2_distance.x;

  if (new_camera_pos.y < this->xy_limit.y)
    final_camera_pos.y = this->xy_limit.y;

  else if (new_camera_wh.y > xy2_limit.y)
    final_camera_pos.y = xy2_distance.y;



  this->camera_pos = final_camera_pos;
  this->ref_pos = new_ref;

}