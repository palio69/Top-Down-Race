#include <game.hpp>



struct { // init_flags

  const int SDL = SDL_INIT_EVERYTHING;
  const int IMG = IMG_INIT_PNG;

} const init_flags;



struct { // win

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



struct { // ren

  const int index = -1;
  const unsigned flags = SDL_RENDERER_ACCELERATED;

  const int r = 0,
    g = 0,
    b = 0,
    a = 255;

} const ren;



struct { // map

  void init() const {
    first_row = "..................................................................";
    tiles =     "..................................................................";
    tiles +=    ".....-----------x--------------------------------------------.....";
    tiles +=    "...-------------x----------------------------------------------...";
    tiles +=    "...-------------x----------------------------------------------...";
    tiles +=    "..--------0-----x-----------------------------------------------..";
    tiles +=    "..--------------x-----------------------------------------------..";
    tiles +=    "..--------------x-----------------------------------------------..";
    tiles +=    "..--------------x-----------------------------------------------..";
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

  mutable std::string first_row, tiles;

  const int tw = 64,
    th = 64;

  const tile origin_tile = { '0', { 32, 0, 16, 16 } },
    finish_tile = { 'x', { 32, 0, 16, 16 } },
    tile1 = { '.', { 16, 0, 16, 16 } },
    tile2 = { '-', { 32, 0, 16, 16 } };

} const map;



struct { // player

  const int w = 64,
    h = 64;
  const SDL_Rect src = { 0, 0, 16, 16 },
    des = { win.w / 2 - w / 2, win.h / 2 - h / 2, w, h };
  const picture spr = { src, des };
  const int rows = 1, columns = 1;

  const float fw = w,
    fh = h;
  const vec2f wh = { fw, fh },

    origin = win.wh / 2.0f - wh / 2.0f,
    pos = origin;
  const float speed = 0.0f,
    goal_speed = 0.0f,
    max_speed = 1250.0f,
    acceleration = 250.0f,
    deceleration = acceleration * 2.0f,
    booster = 1.0f;
  const double angle = 0.0,
    turn_speed = 180.0f;

  mutable ECS::entity ent = 0;
  const input_keys keys;
  const sprite sprt = { spr, rows, columns };
  const position pstn = { origin, pos, angle };
  const movement move = {
    speed,
    goal_speed,
    max_speed,

    acceleration,
    deceleration,
    booster,

    turn_speed
  };

} const player;



struct { // cam

  void init() const {
    const float x = 0.0f,
      y = 0.0f,
      w = map.first_row.size(),
      h = (map.first_row.size() + map.tiles.size()) / w;

    xy_limit = { x, y };
    wh_limit = { w * map.tw, h * map.th };
  }

  mutable vec2f xy_limit, wh_limit;
  const vec2f window_wh = win.wh,
    ref_xy = player.origin,
    ref_wh = player.wh;

} const cam;



bool game::init_dependencies() {
  std::cout << "--- Initializing dependencies...\n";

  const bool SDL_init = SDL_Init(init_flags.SDL),
    IMG_init = IMG_Init(init_flags.IMG) != init_flags.IMG;

  bool initialized = true;



  if (SDL_init) {
    std::cout << "Failed to initialize SDL library\n";
    initialized = false;
  } else
    std::cout << "Initialized SDL successfully!\n";

  if (IMG_init) {
    std::cout << "Failed to initialize SDL_image library\n";
    initialized = false;
  } else
    std::cout << "Initialized SDL_image successfully!\n";



  if (initialized)
    std::cout << "--- Initialized dependecies successfully!\n\n" << std::endl;

  return initialized;
}

bool game::init_objs() {
  std::cout << "--- Initializing essential objects...\n";

  render_system::init(
		      win.title, win.x, win.y, win.w, win.h, win.flags,
		      ren.index, ren.flags,
		      ren.r, ren.g, ren.b, ren.a
		      );
  picture_system::init();

  map.init();
  cam.init();

  bool initialized = true;



  if (!render_system::window()) {
    std::cout << "Failed to initialize window\n";
    initialized = false;
  } else
    std::cout << "Initialized window successfully!\n";

  if (!render_system::renderer()) {
    std::cout << "Failed to initialize renderer\n";
    initialized = false;
  } else
    std::cout << "Initialized renderer successfully!\n";

  if (!picture_system::main_pictures()) {
    std::cout << "Failed to load textures\n";
    initialized = false;
  } else
    std::cout << "Loaded textures successfully!\n";



  if (initialized)
    std::cout << "--- Initialized essential objects successfully!\n\n" << std::endl;

  return initialized;
}

void game::init_systems() {
  event_system::init();
  time_system::init();
}

void game::init() {
  std::cout << "-------| Top Down Race |-------\n\n" << std::endl;

  if (!init_dependencies())
    throw "--- Failed to initialize dependecies";

  if (!init_objs())
    throw "--- Failed to initialize essential objects";

  init_systems();
}

void game::play() {
  try { game::init(); }

  catch(const char* e) {
    std::cout << e << std::endl;
    return;

  } catch(...) {
    std::cout << "ERROR: An unknown error occured" << std::endl;
    return;

  }



  std::cout << "< BEGIN >\n" << std::endl;

  ECS::register_component<input_keys>();
  ECS::register_component<sprite>();
  ECS::register_component<position>();
  ECS::register_component<movement>();

  player.ent = ECS::add_entity();
  ECS::component(player.ent, player.keys);
  ECS::component(player.ent, player.sprt);
  ECS::component(player.ent, player.pstn);
  ECS::component(player.ent, player.move);

  tile_map tm(map.first_row, map.tw, map.th);
  tm.add_to_map(map.tiles);
  tm.add_tile(map.origin_tile);
  tm.add_tile(map.finish_tile);
  tm.add_tile(map.tile1);
  tm.add_tile(map.tile2);

  camera cam1(cam.xy_limit, cam.wh_limit, cam.window_wh, cam.ref_xy, cam.ref_wh);
  car car1(player.ent, cam1);



  auto update = [&car1, &tm, &cam1] () {
    car1.update();
    tm.update(cam1);
  };



  while (event_system::running()) {

    time_system::work();
    event_system::work();

    update();

    picture_system::work();
    render_system::work();

  }



  std::cout << "\n< EXIT >" << std::endl;

  picture_system::quit();
  render_system::quit();

  IMG_Quit();
  SDL_Quit();
}
