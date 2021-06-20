#pragma once

#include <iostream>



#define ASSIGN(op)				  \
  constexpr vec2f& operator op(const vec2f vec) { \
    this->x op vec.x;				  \
    this->y op vec.y;				  \
    return *this;				  \
  }						  \
						  \
  constexpr vec2f& operator op(const float xy) {  \
    this->x op xy;				  \
    this->y op xy;				  \
    return *this;				  \
  }


struct vec2f {
  float x, y;

  ASSIGN(=)
  ASSIGN(+=)
  ASSIGN(-=)
  ASSIGN(*=)
  ASSIGN(/=)

};



std::ostream& operator <<(std::ostream& os, const vec2f vec);



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

inline constexpr vec2f operator +(const vec2f vec1, const float xy) {
  const vec2f vec2 = { (vec1.x + xy), (vec1.y + xy) };
  return vec2;
}

inline constexpr vec2f operator -(const vec2f vec1, const float xy) {
  const vec2f vec2 = { (vec1.x - xy), (vec1.y - xy) };
  return vec2;
}

inline constexpr vec2f operator *(const vec2f vec1, const float xy) {
  const vec2f vec2 = { (vec1.x * xy), (vec1.y * xy) };
  return vec2;
}

inline constexpr vec2f operator /(const vec2f vec1, const float xy) {
  const vec2f vec2 = { (vec1.x / xy), (vec1.y / xy) };
  return vec2;
}

inline constexpr vec2f operator +(const float xy, const vec2f vec1) {
  const vec2f vec2 = { (xy + vec1.x), (xy + vec1.y) };
  return vec2;
}

inline constexpr vec2f operator -(const float xy, const vec2f vec1) {
  const vec2f vec2 = { (xy - vec1.x), (xy - vec1.y) };
  return vec2;
}

inline constexpr vec2f operator *(const float xy, const vec2f vec1) {
  const vec2f vec2 = { (xy + vec1.x), (xy * vec1.y) };
  return vec2;
}

inline constexpr vec2f operator /(const float xy, const vec2f vec1) {
  const vec2f vec2 = { (xy / vec1.x), (xy / vec1.y) };
  return vec2;
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



#undef ASSIGN
