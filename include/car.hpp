#pragma once

#include <cmath>
#include <SDL2/SDL.h>
#include <utils.hpp>
#include <system.hpp>
#include <vec2f.hpp>
#include <picture.hpp>
#include <camera.hpp>
#include <map.hpp>

class car {
private:
  const ECS::entity ent;
  camera& cam;

public:
  car(const ECS::entity ent, camera& cam) : ent(ent), cam(cam) { }
  ~car() { }

  void update();

};
