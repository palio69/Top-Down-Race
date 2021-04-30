#include <game.hpp>



void game::play() {
	if (this->init())
		log_e();



	crd.init();

	crd.register_comp<c_image>();
	crd.register_comp<c_position>();
	crd.register_comp<c_movement>();
	crd.register_comp<c_player_keys>();


	auto rnd = crd.register_sys<renderer>();
	auto phy = crd.register_sys<physics>();
	auto ply = crd.register_sys<player>();

	signature sign;
	sign.set(crd.get_comp_type<c_image>());
	crd.set_sys_signature<renderer>(sign);

	sign.reset();
	sign.set(crd.get_comp_type<c_position>());
	sign.set(crd.get_comp_type<c_movement>());
	crd.set_sys_signature<physics>(sign);

	sign.set(crd.get_comp_type<c_player_keys>());
	crd.set_sys_signature<player>(sign);



	window win = window(this->title, W, H);

	area_manager area_man = area_manager();



	SDL_Event evn;

	float current_time = this->get_current_time();

	while (this->running) {

		const float new_time = this->get_current_time();
		const float delta_time = new_time - current_time;
		current_time = new_time;

		while (SDL_PollEvent(&evn))
			if (evn.type == SDL_QUIT)
				this->running = false;

		const Uint8* key = SDL_GetKeyboardState(nullptr);

		ply->update(key, area_man);
		phy->update(delta_time, area_man);

		log_m();

		win.clear();
		win.update();

	}

	SDL_Quit();
	IMG_Quit();
}

bool game::init() {
	static bool called = false;

	if (called) {
		warnings.push("WARNING: calling \"game::init()\" multiple times");
		return false;

	}

	called = true;
	bool initialized = true;

	if (SDL_Init(SDL_INIT_VIDEO)) {
		errors.push("ERROR: could not initialize SDL library");
		initialized = false;

	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
		errors.push("ERROR: could not initialize SDL_image library");
		initialized = false;

	}

	if (initialized)
	    game::running = true;

	return initialized;
}

SDL_Rect game::make_rect(const vec2f xy, const vec2f wh) const {
	SDL_Rect rec;

	rec.x = std::ceil(xy.x);
	rec.y = std::ceil(xy.y);
	rec.w = std::ceil(wh.x);
	rec.h = std::ceil(wh.y);

	return rec;
}