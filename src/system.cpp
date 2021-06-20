#define INTERN
#include <system.hpp>

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
