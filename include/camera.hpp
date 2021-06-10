#pragma once

#include <vec2f.hpp>

class camera {
private:
  const vec2f xy_limit, wh_limit,
    window_wh;
  vec2f ref_pos,
    camera_pos;

public:
  camera(
	 const vec2f xy_limit, const vec2f wh_limit,
	 const vec2f window_wh,
	 const vec2f ref_pos,
	 const vec2f camera_pos = { 0.0f, 0.0f }
	 ) :
    xy_limit(xy_limit), wh_limit(wh_limit),
    window_wh(window_wh),
    ref_pos(ref_pos),
    camera_pos(camera_pos) { }

  vec2f get_camera_pos() const { return this->camera_pos; }

  void update(const vec2f new_ref);

};