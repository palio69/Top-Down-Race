#pragma once

#include <iostream>



struct vec2f {
  float x, y;

  vec2f& operator =(const vec2f vec);
  vec2f& operator +=(const vec2f vec);
  vec2f& operator -=(const vec2f vec);
  vec2f& operator *=(const vec2f vec);
  vec2f& operator /=(const vec2f vec);

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

std::ostream& operator <<(std::ostream& os, const vec2f vec);
