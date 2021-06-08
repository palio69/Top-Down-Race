#include <map.hpp>


int tile_map::find_tile(const char id) const {

  for (unsigned i = 0; i < this->tiles.size(); ++i) {

    if (this->tiles[i].id == id)
      return i;

  }

  return -1;

}

void tile_map::add_to_map(const std::string tiles) {
  this->map += tiles;
  this->h += tiles.size() / this->w;
}

void tile_map::add_tile(const tile new_tile) {
  this->tiles.push_back(new_tile);
}

void tile_map::render(SDL_Renderer* renderer, const camera cam) const {
  const vec2f cam_pos = cam.get_camera_pos();
  SDL_Rect des = { 0, 0, this->tw, this->th };

  for (int y = 0; y < this->h; ++y) {

    for (int x = 0; x < this->w; ++x) {

      const char id = this->map[x + y * this->w];
      int i = this->find_tile(id);

      if (i < 0)
	continue;

      const auto& t = this->tiles[i];
      des.x = x * des.w - cam_pos.x;
      des.y = y * des.h - cam_pos.y;

      SDL_RenderCopy(renderer, t.sprite.tex, &(t.sprite.src), &des);

    }

  }

}
