#include <camera.hpp>

void camera::update(const vec2f new_ref) {
  const vec2f refs_distance = new_ref - this->ref_pos,
    new_camera_pos = this->camera_pos + refs_distance,
    new_camera_wh = new_camera_pos + this->window_wh,

    xy2_limit = this->xy_limit + this->wh_limit,
    xy2_distance = xy2_limit - this->window_wh;

  vec2f final_camera_pos = new_camera_pos;



  if (new_camera_pos < this->xy_limit)
    final_camera_pos = this->xy_limit;

  else if (new_camera_wh > xy2_limit)
    final_camera_pos = xy2_distance;



  this->camera_pos = final_camera_pos;
  this->ref_pos = new_ref;

}
