#pragma once

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <camera.hpp>
#include <image.hpp>

struct tile {
  char id;
  image sprite;

};

class tile_map {
private:
  std::string map;
  std::vector<tile> tiles;

  int w, h;
  const int tw, th;

  int find_tile(const char id) const;

public:
  tile_map(
	   const std::string first_row,
	   const int tw, const int th
	   ) :
    map(first_row),
    tiles { },
    w(first_row.size()), h(1),
    tw(tw), th(th) { }
  ~tile_map() {
    for (auto& i : this->tiles)
      SDL_DestroyTexture(i.sprite.tex);

  }

  void add_to_map(const std::string tiles);
  void add_tile(const tile new_tile);

  void render(SDL_Renderer* renderer, const camera cam) const;

};
