#define __INTERN__
#include <system.hpp>



bool event_system::running__, event_system::pause__;
float event_system::counter__;
Uint8* event_system::key__;
SDL_Event event_system::event__;

void event_system::init() {
  key__ = 0;
  running__ = true;
  pause__ = false;
}

void event_system::work() {
  const bool empty_counter = counter__ <= 0.0f;

  while (SDL_PollEvent(&event__)) {

    if (event__.type == SDL_QUIT)
      running__ = false;

  }

  key__ = const_cast<Uint8*>(SDL_GetKeyboardState(nullptr));

  if (key__[SDL_SCANCODE_ESCAPE] && empty_counter) {
    pause__ = !pause__;
    std::cout << std::boolalpha << "pause: " << pause__ << std::endl;
    counter__ = 1.0f;
  }

  if (!empty_counter)
    counter__ -= time_system::delta_time();

}



SDL_Window* render_system::window__;
SDL_Renderer* render_system::renderer__;
int render_system::r__,
  render_system::g__,
  render_system::b__,
  render_system::a__;
std::queue<picture> render_system::render_queue__;

void render_system::clear() {
  SDL_SetRenderDrawColor(renderer__, r__, g__, b__, a__);
  SDL_RenderClear(renderer__);
}

void render_system::render(const picture& pic) {
  SDL_RenderCopyEx(
		   renderer__, picture_system::main_pictures(),
		   &(pic.src), &(pic.des),
		   pic.angle, pic.center, pic.flip
		   );
}

void render_system::quit() {
  SDL_DestroyWindow(window__);
  SDL_DestroyRenderer(renderer__);
}

void render_system::init(
			 const char* title,
			 const int x, const int y,
			 const int w, const int h,
			 const unsigned window_flags,

			 const int index,
			 const unsigned renderer_flags,

			 const int r, const int g, const int b, const int a
			 ) {
  window__ = SDL_CreateWindow(title, x, y, w, h, window_flags);
  renderer__ = SDL_CreateRenderer(window__, index, renderer_flags);
  r__ = r;
  g__ = g;
  b__ = b;
  a__ = a;
}

void render_system::work() {

  while (!(render_queue__.empty())) {

    const auto& texture = render_queue__.front();
    render(texture);
    render_queue__.pop();

  }

  update();
  clear();
}



std::string picture_system::path__;
SDL_Texture* picture_system::main_pictures__;
std::stack<picture> picture_system::render_pictures__;

void picture_system::init() {
  path__ = "assets/Top Down Race Sprites.png";
  main_pictures__ = IMG_LoadTexture(render_system::renderer(), path__.data());
}

void picture_system::work() {

  while (!(render_pictures__.empty())) {

    const auto& pic = render_pictures__.top();
    render_system::add_to_queue(pic);
    render_pictures__.pop();

  }

}



float time_system::current_time__;
float time_system::next_time__;
float time_system::delta_time__;

void time_system::init() {
  current_time__ = time();
  next_time__ = 0.0f;
  delta_time__ = 0.0f;
}

void time_system::work() {
  next_time__ = time();
  delta_time__ = next_time__ - current_time__;
  current_time__ = next_time__;
}
