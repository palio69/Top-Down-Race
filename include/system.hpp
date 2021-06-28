#pragma once

#include <string>
#include <stack>
#include <queue>
#include <functional>
#include <bitset>
#include <map>
#include <cstddef>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <picture.hpp>



class render_system {
private:
  render_system() { }
  ~render_system() { }

  static SDL_Window* window__;
  static SDL_Renderer* renderer__;
  static int r__, g__, b__, a__;

  static std::queue<picture> render_queue__;

  static void clear();
  static void update() { SDL_RenderPresent(renderer__); }

public:
  static void add_to_queue(const picture pic) { render_queue__.push(pic); }

  static SDL_Window* window() { return window__; }
  static SDL_Renderer* renderer() { return renderer__; }

  static void render(const picture& pic);
  static void quit();

  static void init(
		   const char title[],
		   const int x, const int y,
		   const int w, const int h,
		   const unsigned window_flags,

		   const int index,
		   const unsigned renderer_flags,

		   const int r, const int g, const int b, const int a
		   );
  static void work();

};

class texture_system {
private:
  texture_system() { }
  ~texture_system() { }

  static std::string path__;
  static SDL_Texture* main_textures__;

  static std::stack<picture> render_textures__;

public:
  static SDL_Texture* main_textures() { return main_textures__; }

  static void add_texture(const picture texture) { render_textures__.push(texture); }
  static void quit() { SDL_DestroyTexture(main_textures__); }

  static void init();
  static void work();

};

class time_system {
private:
  time_system() { }
  ~time_system() { }

  static float current_time__,
    next_time__,
    delta_time__;

public:
  static float delta_time() { return delta_time__; }
  static float time() { return SDL_GetTicks() / 1000.0f; }

  static void init();
  static void work();

};

class ECS {
public:
  typedef std::uint8_t   entity;
  static constexpr entity max_entities = __UINT8_MAX__;

  typedef std::bitset<max_entities>   component_bits;

private:

  class entity_manager {
  private:
    static entity index__;
    static std::map<entity, component_bits> entities__;

  public:
    static entity add_entity();
    static void destroy_entity(const entity ent);

    static void access_entities(std::function<void(const entity&, const component_bits&)>& access);

  };

};
