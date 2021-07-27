#pragma once

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <cstddef>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <picture.hpp>
#include <ECS/ECS.hpp>
#include <ECS/subsystem.hpp>
#include <ECS/component.hpp>



class event_system {
private:
  event_system() { }
  ~event_system() { }

  static bool running__, pause__;
  static float counter__;
  static Uint8* key__;
  static SDL_Event event__;

public:
  static bool running() { return running__; }
  static bool pause() { return pause__; }
  static const Uint8* key() { return key__; }

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

class picture_system {
private:
  picture_system() { }
  ~picture_system() { }

  static std::string path__;
  static SDL_Texture* main_pictures__;

  static std::stack<picture> render_pictures__;

public:
  static SDL_Texture* main_pictures() { return main_pictures__; }

  static void add_picture(const picture pic) { render_pictures__.push(pic); }
  static void quit() { SDL_DestroyTexture(main_pictures__); }

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
