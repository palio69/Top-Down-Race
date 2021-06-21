#include <system.hpp>



float time_system::current_time;
float time_system::next_time;
float time_system::delta_time;



void time_system::init() {
  current_time = get_current_time();
  next_time = 0.0f;
  delta_time = 0.0f;
}

void time_system::work() {
  next_time = get_current_time();
  delta_time = next_time - current_time;
  current_time = next_time;
}
