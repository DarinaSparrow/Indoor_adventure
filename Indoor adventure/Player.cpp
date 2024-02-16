#include "Player.h"


void Player::set_step_x(double x)
{
	step_x = x;
}


void Player::set_step_y(double y)
{
	step_y = y;
}


void Player::move_up(double step)
{
	if (anim_player.get_current_animation_name() != "run_up" and step_x == 0) anim_player.switch_animation("run_up");
	else if (anim_player.get_current_animation_name() != "run_right" and step_x > 0) anim_player.switch_animation("run_right");
	else if (anim_player.get_current_animation_name() != "run_left" and step_x < 0) anim_player.switch_animation("run_left");
	step_y = -step;
}


void Player::move_down(double step)
{
	if (anim_player.get_current_animation_name() != "run_down" and step_x == 0) anim_player.switch_animation("run_down");
	else if (anim_player.get_current_animation_name() != "run_right" and step_x > 0) anim_player.switch_animation("run_right");
	else if (anim_player.get_current_animation_name() != "run_left" and step_x < 0) anim_player.switch_animation("run_left");
	step_y = step;
}

Vector2f Player::get_steps()
{
	return Vector2f(step_x, step_y);
}



void Player::move_left(double step)
{
	if (anim_player.get_current_animation_name() != "run_left") anim_player.switch_animation("run_left");
	step_x = -step;
}


void Player::move_right(double step)
{
	if (anim_player.get_current_animation_name() != "run_right") anim_player.switch_animation("run_right");
	step_x = step;
}


void Player::update(Time const& delta_time)
{
	if (!dead) anim_player.update(delta_time);

	if (step_x == 0 and step_y == 0) anim_player.switch_animation("static");

	time_update += delta_time;
	time_damage += delta_time;
	if (time_damage > microseconds(1000000)) {
		time_damage = microseconds(0);
		sprite_player.setColor(Color::White);
	}

	if (time_update > microseconds(3))
	{
		time_update = microseconds(0);

		if (!dead) {
			sprite_player.move(step_x, step_y);
			if (sprite_player.getPosition().x < borders.x) {
				sprite_player.setPosition(borders.x, sprite_player.getPosition().y);
			}
			if (sprite_player.getPosition().x > borders.max_x - sprite_player.getGlobalBounds().width) {
				sprite_player.setPosition(borders.max_x - sprite_player.getGlobalBounds().width, sprite_player.getPosition().y);
			}
			if (sprite_player.getPosition().y < borders.y) {
				sprite_player.setPosition(sprite_player.getPosition().x, borders.y);
			}
			if (sprite_player.getPosition().y > borders.max_y - sprite_player.getGlobalBounds().height) {
				sprite_player.setPosition(sprite_player.getPosition().x, borders.max_y - sprite_player.getGlobalBounds().height);
			}
		}
		else {
			sprite_player.setColor(Color::Red);
		}
	}
}


void Player::set_borders_player(double x, double y, double max_x, double max_y)
{
	borders.x = x;
	borders.y = y;
	borders.max_x = max_x;
	borders.max_y = max_y;
}


Sprite& Player::get_player()
{
	return sprite_player;
}

RectangleShape& Player::get_bords()
{
	return border;
}

GameSound& Player::get_sound()
{
	return game_sound;
}

string Player::get_cur_anim()
{
	return anim_player.get_current_animation_name();
}

void Player::catch_bonus(Gun& obj, Game& rules, Bonus& coins)
{
	int num = coins.GetTotal();
	for (int i = 0; i < num; i++) {
		if (sprite_player.getGlobalBounds().contains(Vector2f(coins.get_coins()[i].sprite_coin.getGlobalBounds().left + coins.get_coins()[i].sprite_coin.getGlobalBounds().width / 2.0,
			coins.get_coins()[i].sprite_coin.getGlobalBounds().top + coins.get_coins()[i].sprite_coin.getGlobalBounds().height / 2.0))) {
			coins.get_coins()[i].sprite_coin.setPosition(Vector2f(-coins.get_coins()[i].sprite_coin.getPosition().x, -coins.get_coins()[i].sprite_coin.getPosition().y));
			rules.update_score();
			sprite_player.setColor(Color::Green);
		}

		//if (coins->get_coins()[i].sprite_coin.getGlobalBounds().contains(Vector2f(obj.get_bul().getPosition().x + obj.get_bul().getGlobalBounds().width / 2.0,
		//	obj.get_bul().getPosition().y + obj.get_bul().getGlobalBounds().height / 2.0))) {
		//	coins->get_coins()[i].sprite_coin.setPosition(Vector2f(-coins->get_coins()[i].sprite_coin.getPosition().x, -coins->get_coins()[i].sprite_coin.getPosition().y));
		//	if (sprite_player.getGlobalBounds().contains(Vector2f(obj.get_bul().getPosition().x, obj.get_bul().getPosition().y))) {
		//		rules.update_score();
		//		sprite_player.setColor(Color::Green);
		//	}
		//	obj.refresh_bul();
		//}
	}
}

void Player::set_position(double x, double y)
{
	sprite_player.setPosition(Vector2f(x, y));
}

void Player_static::set_dead(bool fl)
{
	dead = fl;
}

bool Player_static::get_dead() const
{
	return dead;
}

void Player_static::set_visible(bool fl)
{
	visible = fl;
}

bool Player_static::get_visible()
{
	return visible;
}

void Player_static::set_slide(bool fl)
{
	slide = fl;
}

bool Player_static::get_slide()
{
	return slide;
}

void Player_static::set_fire(bool fl)
{
	fire = fl;
}

bool Player_static::get_fire()
{
	return fire;
}

tuple<bool, bool, bool, bool> Player_static::get_params()
{
	return tuple<bool, bool, bool, bool>(dead, visible, slide, fire);
}


void Player_vector::set_dead(bool fl)
{
	dead = fl;
}

bool Player_vector::get_dead() const
{
	return dead;
}

void Player_vector::set_visible(bool fl)
{
	visible = fl;
}

bool Player_vector::get_visible()
{
	return visible;
}

void Player_vector::set_slide(bool fl)
{
	slide = fl;
}

bool Player_vector::get_slide()
{
	return slide;
}

void Player_vector::set_fire(bool fl)
{
	fire = fl;
}

bool Player_vector::get_fire()
{
	return fire;
}

tuple<bool, bool, bool, bool> Player_vector::get_params()
{
	return tuple<bool, bool, bool, bool>(dead, visible, slide, fire);
}


void Player_invisible::set_dead(bool fl)
{
	dead = fl;
}

bool Player_invisible::get_dead() const
{
	return dead;
}

void Player_invisible::set_visible(bool fl)
{
	visible = fl;
}

bool Player_invisible::get_visible()
{
	return visible;
}

void Player_invisible::set_slide(bool fl)
{
	slide = fl;
}

bool Player_invisible::get_slide()
{
	return slide;
}

void Player_invisible::set_fire(bool fl)
{
	fire = fl;
}

bool Player_invisible::get_fire()
{
	return fire;
}


tuple<bool, bool, bool, bool> Player_invisible::get_params()
{
	return tuple<bool, bool, bool, bool>(dead, visible, slide, fire);
}


void Player_danger_zone::set_dead(bool fl)
{
	dead = fl;
}

bool Player_danger_zone::get_dead() const
{
	return dead;
}

void Player_danger_zone::set_visible(bool fl)
{
	visible = fl;
}

bool Player_danger_zone::get_visible()
{
	return visible;
}

void Player_danger_zone::set_slide(bool fl)
{
	slide = fl;
}

bool Player_danger_zone::get_slide()
{
	return slide;
}

void Player_danger_zone::set_fire(bool fl)
{
	fire = fl;
}

bool Player_danger_zone::get_fire()
{
	return fire;
}


tuple<bool, bool, bool, bool> Player_danger_zone::get_params()
{
	return tuple<bool, bool, bool>(dead, visible, slide);
}

