#include <map.hpp>



void tile_map::add_to_map(const std::string tiles) {
  this->map += tiles;
  this->h += tiles.size() / this->w;
}

void tile_map::add_tile(const tile new_tile) {
  this->tiles.push_back(new_tile);
}
