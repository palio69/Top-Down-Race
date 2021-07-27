#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <vec2f.hpp>
#include <system.hpp>
#include <camera.hpp>
#include <picture.hpp>

struct tile {
  char id;
  picture sprite;

};

class tile_map {
private:
  std::string map;
  std::vector<tile> tiles;

  int w, h;
  const int tw, th;

public:
  tile_map(
	   const std::string first_row,
	   const int tw, const int th
	   ) :
    map(first_row),
    tiles { },
    w(first_row.size()), h(1),
    tw(tw), th(th) { }
  ~tile_map() { }

  void add_to_map(const std::string tiles);
  void add_tile(const tile new_tile) { this->tiles.push_back(new_tile); }

  int find_tile(const char id) const;
  vec2f find_tile_xy(const char id) const;

  void update(const camera cam) const;

};
