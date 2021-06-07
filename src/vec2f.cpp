#include <vec2f.hpp>

vec2f& vec2f::operator =(const vec2f vec) {
  this->x = vec.x;
  this->y = vec.y;
  return *this;
}

vec2f& vec2f::operator +=(const vec2f vec) {
  this->x += vec.x;
  this->y += vec.y;
  return *this;
}

vec2f& vec2f::operator -=(const vec2f vec) {
  this->x -= vec.x;
  this->y -= vec.y;
  return *this;
}

vec2f& vec2f::operator *=(const vec2f vec) {
  this->x *= vec.x;
  this->y *= vec.y;
  return *this;
}

vec2f& vec2f::operator /=(const vec2f vec) {
  this->x /= vec.x;
  this->y /= vec.y;
  return *this;
}

std::ostream& operator <<(std::ostream& os, const vec2f vec) {
  os << "{ " << vec.x << ", " << vec.y << " }";
  return os;
}
