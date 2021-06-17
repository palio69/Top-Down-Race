#include <game.hpp>



const char path[] = "assets/Top Down Race Sprites.png";
SDL_Texture* textures = nullptr;

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
  const vec2f wh = { fw, fh };

} const win;

struct {
  const int index = -1;
  const unsigned flags = SDL_RENDERER_ACCELERATED;

  const int r = 0,
    g = 0,
    b = 0,
    a = 255;

} const ren;

struct {
  void init() {
    first_row = "..................................................................";
    tiles =     "..................................................................";
    tiles +=    ".....--------------------------------------------------------.....";
    tiles +=    "...------------------------------------------------------------...";
    tiles +=    "...------------------------------------------------------------...";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "..-----------........................................-----------..";
    tiles +=    "..---------............................................---------..";
    tiles +=    "..--------..............................................--------..";
    tiles +=    "..--------..............................................--------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..-------................................................-------..";
    tiles +=    "..--------..............................................--------..";
    tiles +=    "..--------..............................................--------..";
    tiles +=    "..---------............................................---------..";
    tiles +=    "..-----------........................................-----------..";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "..--------------------------------------------------------------..";
    tiles +=    "...------------------------------------------------------------...";
    tiles +=    "...------------------------------------------------------------...";
    tiles +=    ".....-------------------------------------------------------......";
    tiles +=    "..................................................................";
    tiles +=    "..................................................................";
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
  const vec2f wh = { fw, fh },

    pos = win.wh / 2.0f - wh / 2.0f;
  const float max_speed = 1250.0f;
  const double angle = 0.0;

} const player;

struct {
  void init() {
    const float x = 0.0f,
      y = 0.0f,
      w = map.first_row.size(),
      h = (map.first_row.size() + map.tiles.size()) / w;

    xy_limit = { x, y };
    wh_limit = { w * map.tw, h * map.th };
  }

  vec2f xy_limit, wh_limit;
  const vec2f window_wh = win.wh,
    ref_pos = player.pos;

} cam;



void game::init(SDL_Window*& window, SDL_Renderer*& renderer) {
  auto init_dependencies = [] {
    std::cout << "--- initializing dependencies...\n";

    const bool SDL_init = SDL_Init(init_flags.SDL),
    IMG_init = IMG_Init(init_flags.IMG) != init_flags.IMG;

    bool initialized = true;



    if (SDL_init) {
      std::cout << "ERROR: could not initialize SDL library\n";
      initialized = false;
    } else
      std::cout << "initialized SDL successfully!\n";

    if (IMG_init) {
      std::cout << "ERROR: could not initialize SDL_image library\n";
      initialized = false;
    } else
      std::cout << "initialized SDL_image successfully!\n";



    if (initialized)
      std::cout << "--- initialized dependecies successfully!\n\n" << std::endl;

    return initialized;

  };

  auto init_objs = [&window, &renderer] {
    std::cout << "--- initializing essential variables and objects...\n";

    window = SDL_CreateWindow(win.title, win.x, win.y, win.w, win.h, win.flags);
    renderer = SDL_CreateRenderer(window, ren.index, ren.flags);
    textures = IMG_LoadTexture(renderer, path);

    bool initialized = true;



    if (!window) {
      std::cout << "failed to initialize window\n";
      initialized = false;
    } else
      std::cout << "initialized window successfully!\n";

    if (!renderer) {
      std::cout << "failed to initialize renderer\n";
      initialized = false;
    } else
      std::cout << "initialized renderer successfully!\n";

    if (!textures) {
      std::cout << "failed to load textures\n";
      initialized = false;
    } else
      std::cout << "loaded textures successfully!\n";



    if (initialized)
      std::cout << "--- initialized essential variables and objects successfully!\n\n" << std::endl;

    return initialized;

  };



  std::cout << "-------| Top Down Race |-------\n\n" << std::endl;

  if (!init_dependencies())
    throw "--- failed to initialize dependecies";

  if (!init_objs())
    throw "--- failed to initialize essential variables and objects";

}

void game::play() {
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  try { game::init(window, renderer); }

  catch(const char* e) {
    std::cout << e << std::endl;
    return;

  } catch(...) {
    std::cout << "an unknown error occured" << std::endl;
    return;

  }



  std::cout << "< BEGIN >\n" << std::endl;

  map.init();
  cam.init();

  float current_time = game::get_current_time(),
    next_time = 0.0f,
    delta_time = 0.0f;

  const SDL_Rect null_des = { 0, 0, 0, 0 };

  tile_map tm(map.first_row, map.tw, map.th);
  tm.add_to_map(map.tiles);
  tm.add_tile( { map.tile1, { textures, map.src1, null_des } } );
  tm.add_tile( { map.tile2, { textures, map.src2, null_des } } );

  camera cam1(cam.xy_limit, cam.wh_limit, cam.window_wh, cam.ref_pos);
  car car1(
	   player.pos, player.max_speed, player.angle,
	   &tm, cam1,
	   { textures, player.src, player.des }, player.flip
	   );



  auto update = [&car1, &cam1] (const Uint8* key, const float delta_time) {
    car1.update(key, delta_time);
  };

  auto clear_window = [&renderer] {
    SDL_SetRenderDrawColor(renderer, ren.r, ren.g, ren.b, ren.a);
    SDL_RenderClear(renderer);
  };

  auto render = [&renderer, &tm, &car1, &cam1] {
    tm.render(renderer, cam1);
    car1.render(renderer);
  };

  auto update_window = [&renderer] {
    SDL_RenderPresent(renderer);
  };



  bool running = true;
  SDL_Event evn;

  while (running) {

    next_time = game::get_current_time();
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



  std::cout << "\n< EXIT >" << std::endl;

  SDL_DestroyTexture(textures);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);

  IMG_Quit();
  SDL_Quit();
}
