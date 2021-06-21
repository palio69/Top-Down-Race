#include <system.hpp>



float time_system::current_time__;
float time_system::next_time__;
float time_system::delta_time__;



void time_system::init() {
  current_time__ = time();
  next_time__ = 0.0f;
  delta_time__ = 0.0f;
}

void time_system::work() {
  next_time__ = time();
  delta_time__ = next_time__ - current_time__;
  current_time__ = next_time__;
}
