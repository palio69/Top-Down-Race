#include <window.hpp>

#define W 720
#define H 480

int main(int argc, char* argv[]) {
  SDL_Init(SDL_INIT_EVERYTHING);
  
  window win("Top-Down Race", W, H);

  bool running = true;
  SDL_Event evn;
  
  while(running) {

    while(SDL_PollEvent(&evn)) {

      if (evn.type == SDL_QUIT)
	running = false;

    }

    win.clear();
    win.update();

  }

  SDL_Quit();
  return 0;
}
