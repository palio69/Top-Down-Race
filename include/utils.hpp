#pragma once

#include <SDL2/SDL.h>

#define TKN(a) #a
#define CAT(a, b) a##b
#define KEY(key) CAT(SDL_SCANCODE_, key)

using key = SDL_Scancode;

constexpr double pi = 3.141592654;

inline constexpr double to_radians(const double angle) { return angle * pi / 180; }
inline constexpr double to_degrees(const double angle) { return angle * 180 / pi; }
