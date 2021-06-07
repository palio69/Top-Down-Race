#include <game.hpp>



struct {
  const int SDL = SDL_INIT_EVERYTHING;
  const int IMG = IMG_INIT_PNG;

} const init_flags;

struct {
  const char* title = "Top Down Race";
  const int x = SDL_WINDOWPOS_CENTERED,
    y = SDL_WINDOWPOS_CENTERED,
    w = 720,
    h = 480;
  const unsigned flags = SDL_WINDOW_SHOWN;

  const float fw = w,
    fh = h;

} const win;

struct {
  const int index = -1;
  const unsigned flags = SDL_RENDERER_ACCELERATED;

} const ren;

struct {
  void init() {
    first_row = ".....---....";
    tiles +=    "....-----...";
    tiles +=    "...---.---..";
    tiles +=    "..---...---.";
    tiles +=    ".-----------";
    tiles +=    "---.......--";
    tiles +=    "--.........-";
    tiles +=    "-...........";
  }

  std::string first_row, tiles;

  const int tw = 64,
    th = 64;

  const char tile1 = '.',
    tile2 = '-';
  const SDL_Rect src1 = { 16, 0, 16, 16 },
    src2 = { 32, 0, 16, 16 };

} map;

struct {
  const int w = 64,
    h = 64;
  const SDL_Rect src = { 0, 0, 16, 16 },
    des = { win.w / 2 - w / 2, win.h / 2 - h / 2, w, h };
  const SDL_RendererFlip flip = SDL_FLIP_NONE;

  const float fw = w,
    fh = h;

  const vec2f pos = { win.fw / 2 - fw / 2, win.fh / 2 - fh / 2 };
  const float max_speed = 100.0f;
  const double angle = 0.0;

} const player;

const char* path = "assets/Top Down Race Sprites.png";
SDL_Texture* textures = nullptr;



void game::init(SDL_Window*& window, SDL_Renderer*& renderer) const {
  std::cout << "- initializing dependencies...\n\n";

  if (SDL_Init(init_flags.SDL))
    throw "ERROR: could not initialize SDL library\n";
  std::cout << "initialized SDL sucefully!\n";

  if (IMG_Init(init_flags.IMG) != init_flags.IMG)
    throw "ERROR: could not initialize SDL_image library\n";
  std::cout << "initialized SDL_image sucefully!\n";

  std::cout << "\n- initialized dependecies sucefully...!\n\n";



  std::cout << "\n- initializing essential variables and objects...\n\n";

  window = SDL_CreateWindow(win.title, win.x, win.y, win.w, win.h, win.flags);
  if (!window) {
    std::cout << "failed to initialize window\n";
    return;

  }
  std::cout << "initialized window sucefully!\n";

  renderer = SDL_CreateRenderer(window, ren.index, ren.flags);
  if (!renderer) {
    std::cout << "failed to initialize renderer\n";
    return;

  }
  std::cout << "initialized renderer sucefully!\n";

  textures = IMG_LoadTexture(renderer, path);
  if (!textures) {
    std::cout << "failed to load textures";
    return;

  }
  std::cout << "loaded textures sucefully!\n";

  std::cout << "\n- initialized essential variables and objects sucefully...!\n\n";
}

void game::play() const {
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  try { this->init(window, renderer); }

  catch(const char* e) {
    std::cout << e;
    return;

  } catch(...) {
    std::cout << "an unknown error occured\n";
    return;

  }



  float current_time = this->get_current_time(),
    next_time = 0.0f,
    delta_time = 0.0f;

  const SDL_Rect null_des = { 0, 0, 0, 0 };

  map.init();
  tile_map tm(map.first_row, map.tw, map.th);
  tm.add_to_map(map.tiles);
  tm.add_tile( { map.tile1, { textures, map.src1, null_des } } );
  tm.add_tile( { map.tile2, { textures, map.src2, null_des } } );

  car car1(player.pos, player.max_speed, player.angle, { textures, player.src, player.des }, player.flip);



  auto update = [&car1] (const Uint8* key, const float delta_time) {
    car1.update(key, delta_time);
  };

  auto clear_window = [&renderer] {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
  };

  auto render = [&renderer, &car1, &tm] {
    tm.render(renderer);
    car1.render(renderer);
  };

  auto update_window = [&renderer] {
    SDL_RenderPresent(renderer);
  };



  bool running = true;
  SDL_Event evn;

  while (running) {

    next_time = this->get_current_time();
    delta_time = next_time - current_time;
    current_time = next_time;

    while(SDL_PollEvent(&evn)) {

      if (evn.type == SDL_QUIT)
	running = false;

    }

    const Uint8* key = SDL_GetKeyboardState(nullptr);

    update(key, delta_time);

    clear_window();
    render();
    update_window();

  }



  std::cout << "\n- exiting...\n";
  IMG_Quit();
  SDL_Quit();
}
