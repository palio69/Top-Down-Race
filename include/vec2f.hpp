#pragma once

#include <iostream>

struct vec2f { float x, y; };

std::ostream& operator << (std::ostream& os, const vec2f vec);
