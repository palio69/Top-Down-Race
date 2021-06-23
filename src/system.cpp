#include <system.hpp>



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



std::string texture_system::path__;
SDL_Texture* texture_system::main_textures__;
std::stack<picture> texture_system::render_textures__;

void texture_system::init() {
  path__ = "assets/Top Down Race Sprites.png";
  main_textures__ = IMG_LoadTexture(render_system::renderer(), path__.data());
  render_textures__ = { };
}

void texture_system::work() {

  while (!(render_textures__.empty())) {

    const auto texture = render_textures__.top();
    render_system::add_to_stack(texture);
    render_textures__.pop();

  }

}



SDL_Window* render_system::window__;
SDL_Renderer* render_system::renderer__;
int render_system::r__,
  render_system::g__,
  render_system::b__,
  render_system::a__;
std::stack<picture> render_system::render_stack__;

void render_system::clear() {
  SDL_SetRenderDrawColor(renderer__, r__, g__, b__, a__);
  SDL_RenderClear(renderer__);
}

void render_system::render(const picture& pic) {
  SDL_RenderCopyEx(
		   renderer__, texture_system::main_textures(),
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
  render_stack__ = { };
}

void render_system::work() {

  while (!(render_stack__.empty())) {

    const auto texture = render_stack__.top();
    render(texture);
    render_stack__.pop();

  }

  update();
  clear();
}
