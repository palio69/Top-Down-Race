#include <vec2f.hpp>

std::ostream& operator <<(std::ostream& os, const vec2f vec) {
  os << "{ " << vec.x << ", " << vec.y << " }";
  return os;
}
