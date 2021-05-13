#pragma once



#include <ostream>
#include <cmath>



class vec2f {
public:
  vec2f() { }
  vec2f(const float xy) :
    x(xy), y(xy) { }
  vec2f(const float x, const float y) :
    x(x), y(y) { }
  ~vec2f() { }

  float x, y;

  void reset();

  float get_length() const;
  float get_length_sqr() const;

  vec2f normalize() const;
  float get_dot_product(const vec2f other) const;

  vec2f operator+(const vec2f other) const;
  vec2f operator-(const vec2f other) const;
  vec2f operator*(const vec2f other) const;
  vec2f operator/(const vec2f other) const;

  vec2f& operator=(const vec2f new_vec);

  friend bool operator==(const vec2f lhs, const vec2f rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
  }
  friend bool operator!=(const vec2f lhs, const vec2f rhs) {
    return (lhs.x != rhs.x && lhs.y != rhs.y);
  }
  friend bool operator>(const vec2f lhs, const vec2f rhs) {
    return (lhs.x > rhs.x && lhs.y > rhs.y);
  }
  friend bool operator<(const vec2f lhs, const vec2f rhs) {
    return (lhs.x < rhs.x && lhs.y < rhs.y);
  }
  friend bool operator>=(const vec2f lhs, const vec2f rhs) {
    return (lhs.x >= rhs.x && lhs.y >= rhs.y);
  }
  friend bool operator<=(const vec2f lhs, const vec2f rhs) {
    return (lhs.x <= rhs.x && lhs.y <= rhs.y);
  }

  friend std::ostream& operator<<(std::ostream& os, const vec2f vec);
  friend std::wostream& operator<<(std::wostream& wos, const vec2f vec);

};
