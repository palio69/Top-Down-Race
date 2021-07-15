#include <system.hpp>



bool event_system::running__;
SDL_Event event_system::event__;

void event_system::init() {
  running__ = true;
}

void event_system::work() {

  while (SDL_PollEvent(&event__)) {

    if (event__.type == SDL_QUIT)
      running__ = false;

  }

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



std::string texture_system::path__;
SDL_Texture* texture_system::main_textures__;
std::stack<picture> texture_system::render_textures__;

void texture_system::init() {
  path__ = "assets/Top Down Race Sprites.png";
  main_textures__ = IMG_LoadTexture(render_system::renderer(), path__.data());
}

void texture_system::work() {

  while (!(render_textures__.empty())) {

    const auto& texture = render_textures__.top();
    render_system::add_to_queue(texture);
    render_textures__.pop();

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



unsigned ECS::entity_manager::index__ = 0;
std::map<ECS::entity, ECS::component_bits> ECS::entity_manager::entities__ { };
std::vector<ECS::function> ECS::entity_manager::observers__ { };

ECS::component_id ECS::component_manager::current_id__ = 0;
std::map<const char*, ECS::component_id> ECS::component_manager::ids__ { };
std::map<ECS::component_id, std::shared_ptr<ECS::base_component_container>> ECS::component_manager::containers__ { };
