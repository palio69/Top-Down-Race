#include <camera.hpp>

void camera::update(const vec2f new_ref) {
  const vec2f distance = new_ref - this->ref_pos;
  this->ref_pos = new_ref;
  this->camera_pos += distance;
}
