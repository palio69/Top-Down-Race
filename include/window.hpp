#pragma once



#include <SDL2/SDL.h>



class window {
private:
  SDL_Window* win;
  SDL_Renderer* ren;

public:
  window(const char* title, const int w, const int h) :
    win(nullptr), ren(nullptr) {
    this->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    this->ren = SDL_CreateRenderer(this->win, -1, SDL_RENDERER_ACCELERATED);
  }
  ~window() {
    SDL_DestroyWindow(this->win);
    SDL_DestroyRenderer(this->ren);
  }

  void clear() const { SDL_RenderClear(this->ren); }
  void update() const { SDL_RenderPresent(this->ren); }
};
