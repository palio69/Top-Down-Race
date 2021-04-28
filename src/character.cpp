#include <character.hpp>



void character::switch_current_sprite(sprite& new_sprite) {
	if (&new_sprite == this->current_sprite)
		return;

	current_sprite->change_frame_pos(0, 0);
	current_sprite = &(new_sprite);
}

void character::update_sprites() {
	if (this->current_sprite != nullptr)
		this->current_sprite->advance();



	if (this->goal_vel != vec2f(0)) {

		if (this->dir.y > 0)
			this->switch_current_sprite(this->u_sprites[MOVE]);

		else if (this->dir.y < 0)
			this->switch_current_sprite(this->d_sprites[MOVE]);

		else if (this->dir.x > 0)
			this->switch_current_sprite(this->r_sprites[MOVE]);

		else
			this->switch_current_sprite(this->l_sprites[MOVE]);

	} else {

		if (this->dir.y > 0)
			this->switch_current_sprite(this->u_sprites[IDLE]);

		else if (this->dir.y < 0)
			this->switch_current_sprite(this->d_sprites[IDLE]);

		else if (this->dir.x > 0)
			this->switch_current_sprite(this->r_sprites[IDLE]);

		else
			this->switch_current_sprite(this->l_sprites[IDLE]);

	}

}

void character::update_pos(const float delta_time, const area_manager area_man) {
	vec2f xy2 = vec2f(this->xy.x + this->wh.x, this->xy.y + this->wh.y), diff = vec2f(0, 0),
		move = vec2f(this->vel * vec2f(delta_time));

	float fric = area_man.get_fric(this->xy, xy2);

	if (area_man.check_up_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("up collision detected");

		if (this->vel.y < 0) {
			this->vel.y = 0;
			move.y += diff.y;

		}

	}

	if (area_man.check_down_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("down collision detected");

		if (this->vel.y > 0) {
			this->vel.y = 0;
			move.y += diff.y;

		}

	}

	if (area_man.check_right_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("right collision detected");

		if (this->vel.x > 0) {
			this->vel.x = 0;
			move.x += diff.x;

		}

	}

	if (area_man.check_left_collision(this->xy + move, xy2 + move, &diff)) {
		msgs.push("left collision detected");

		if (this->vel.x < 0) {
			this->vel.x = 0;
			move.x += diff.x;

		}

	}



	if (std::ceil(this->vel.x))
		this->xy.x += move.x;

	if (std::ceil(this->vel.y))
		this->xy.y += move.y;



	if (std::ceil(this->vel.x) < std::ceil(this->goal_vel.x))
		this->vel.x += delta_time * fric;

	else if (std::ceil(this->vel.x) > std::ceil(this->goal_vel.x))
		this->vel.x -= delta_time * fric;



	if (std::ceil(this->vel.y) < std::ceil(this->goal_vel.y))
		this->vel.y += delta_time * fric;

	else if (std::ceil(this->vel.y) > std::ceil(this->goal_vel.y))
		this->vel.y -= delta_time * fric;

}

void character::update_datas(const Uint8* key) {
	if (key[SDL_SCANCODE_UP]) {
		this->goal_vel.y = -(this->max_vel.y);
		this->dir.y = -1;

	} else if (key[SDL_SCANCODE_DOWN]) {
		this->goal_vel.y = this->max_vel.y;
		this->dir.y = 1;

	} else
		this->goal_vel.y = 0;



	if (key[SDL_SCANCODE_RIGHT]) {
		this->goal_vel.x = this->max_vel.x;
		this->dir.x = 1;

	} else if (key[SDL_SCANCODE_LEFT]) {
		this->goal_vel.x = -(this->max_vel.x);
		this->dir.x = -1;

	} else
		this->goal_vel.x = 0;



	if (key[SDL_SCANCODE_Z] && !(this->counter)) {

		if (this->is_running) {
			this->max_vel = this->max_vel / vec2f(2, 2);
			this->is_running = false;

		} else {
			this->max_vel = this->max_vel * vec2f(2, 2);
			this->is_running = true;

		}

		this->counter = 10;

	}



	if (this->counter)
		--counter;

}