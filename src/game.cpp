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

    origin = win.wh / 2.0f - wh / 2.0f;
  const float max_speed = 1250.0f,
    acceleration = 250.0f,
    deceleration = acceleration * 2.0f;
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
    ref_xy = player.origin,
    ref_wh = player.wh;

} cam;



void game::init() {
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

  auto init_objs = [] {
    std::cout << "--- initializing essential variables and objects...\n";

    render_system::init(
			win.title, win.x, win.y, win.w, win.h, win.flags,
			ren.index, ren.flags,
			ren.r, ren.g, ren.b, ren.a
			);
    sprite_system::init();

    bool initialized = true;



    if (!render_system::window()) {
      std::cout << "failed to initialize window\n";
      initialized = false;
    } else
      std::cout << "initialized window successfully!\n";

    if (!render_system::renderer()) {
      std::cout << "failed to initialize renderer\n";
      initialized = false;
    } else
      std::cout << "initialized renderer successfully!\n";

    if (!sprite_system::textures()) {
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
  try { game::init(); }

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
  time_system::init();

  const SDL_Rect null_des = { 0, 0, 0, 0 };

  tile_map tm(map.first_row, map.tw, map.th);
  tm.add_to_map(map.tiles);
  tm.add_tile( { map.tile1, { sprite_system::textures(), map.src1, null_des } } );
  tm.add_tile( { map.tile2, { sprite_system::textures(), map.src2, null_des } } );

  camera cam1(cam.xy_limit, cam.wh_limit, cam.window_wh, cam.ref_xy, cam.ref_wh);
  car car1(
	   player.origin, player.max_speed,
	   player.acceleration, player.deceleration,
	   player.angle,

	   cam1,
	   { sprite_system::textures(), player.src, player.des }, player.flip
	   );



  auto update = [&car1, &cam1] (const Uint8* key) {
    car1.update(key);
  };


  auto render = [&tm, &car1, &cam1] {
    tm.render(render_system::renderer(), cam1);
    car1.render(render_system::renderer());
  };



  bool running = true;
  SDL_Event evn;

  while (running) {

    time_system::work();

    while(SDL_PollEvent(&evn)) {

      if (evn.type == SDL_QUIT)
	running = false;

    }

    const Uint8* key = SDL_GetKeyboardState(nullptr);

    update(key);
    render_system::work(render);

  }



  std::cout << "\n< EXIT >" << std::endl;

  SDL_DestroyTexture(textures);
  render_system::quit();

  IMG_Quit();
  SDL_Quit();
}
