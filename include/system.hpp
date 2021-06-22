#pragma once

#include <string>
#include <functional>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <image.hpp>



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

class sprite_system {
private:
  sprite_system() { }
  ~sprite_system() { }

  static std::string path__;
  static SDL_Texture* textures__;

public:
  static SDL_Texture* textures() { return textures__; }

  static void quit() { SDL_DestroyTexture(textures__); }

  static void init();
  static void work();

};

class render_system {
private:
  render_system() { }
  ~render_system() { }

  static SDL_Window* window__;
  static SDL_Renderer* renderer__;
  static int r__, g__, b__, a__;

  static void clear();
  static void update() { SDL_RenderPresent(renderer__); }

public:
  static SDL_Window* window() { return window__; }
  static SDL_Renderer* renderer() { return renderer__; }

  static void render(const image& img);
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
  static void work(std::function<void()> fn);

};
