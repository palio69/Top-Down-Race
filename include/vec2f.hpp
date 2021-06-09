#pragma once

#include <iostream>



struct vec2f {
  float x, y;

  constexpr vec2f& operator =(const vec2f vec) {
    this->x = vec.x;
    this->y = vec.y;
    return *this;
  }
  constexpr vec2f& operator +=(const vec2f vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
  }
  constexpr vec2f& operator -=(const vec2f vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
  }
  constexpr vec2f& operator *=(const vec2f vec) {
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
  }
  constexpr vec2f& operator /=(const vec2f vec) {
    this->x /= vec.x;
    this->y /= vec.y;
    return *this;
  }

};



inline constexpr vec2f operator +(const vec2f vec1, const vec2f vec2) {
  const vec2f vec3 = { (vec1.x + vec2.x), (vec1.y + vec2.y) };
  return vec3;
}

inline constexpr vec2f operator -(const vec2f vec1, const vec2f vec2) {
  const vec2f vec3 = { (vec1.x - vec2.x), (vec1.y - vec2.y) };
  return vec3;
}

inline constexpr vec2f operator *(const vec2f vec1, const vec2f vec2) {
  const vec2f vec3 = { (vec1.x * vec2.x), (vec1.y * vec2.y) };
  return vec3;
}

inline constexpr vec2f operator /(const vec2f vec1, const vec2f vec2) {
  const vec2f vec3 = { (vec1.x / vec2.x), (vec1.y / vec2.y) };
  return vec3;
}



inline constexpr bool operator ==(const vec2f lhs, const vec2f rhs) {
  return (lhs.x == rhs.x && lhs.y == rhs.y);
}

inline constexpr bool operator !=(const vec2f lhs, const vec2f rhs) {
  return (lhs.x != rhs.x || lhs.y != rhs.y);
}

inline constexpr bool operator >(const vec2f lhs, const vec2f rhs) {
  return (lhs.x + lhs.y > rhs.x + rhs.y);
}

inline constexpr bool operator <(const vec2f lhs, const vec2f rhs) {
  return (lhs.x + lhs.y < rhs.x + rhs.y);
}

inline constexpr bool operator >=(const vec2f lhs, const vec2f rhs) {
  return (lhs.x + lhs.y >= rhs.x + rhs.y);
}

inline constexpr bool operator <=(const vec2f lhs, const vec2f rhs) {
  return (lhs.x + lhs.y <= rhs.x + rhs.y);
}



std::ostream& operator <<(std::ostream& os, const vec2f vec);
