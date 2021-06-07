#pragma once

#include <vec2f.hpp>

class camera {
private:
  vec2f ref_pos;
  vec2f camera_pos;

public:
  camera(const vec2f ref_pos) :
    ref_pos(ref_pos), camera_pos { 0.0f, 0.0f } { }

  void update(const vec2f new_ref);

};
