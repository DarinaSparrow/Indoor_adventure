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
	if (sprite_player.getPosition().y > borders.y) {
		step_y = -step;
	}
}


void Player::move_down(double step)
{
	if (sprite_player.getPosition().y < borders.max_y) {
		step_y = step;
	}
}


void Player::move_left(double step)
{
	if (sprite_player.getPosition().x > borders.x) {
		if (anim_player.get_current_animation_name() != "run_left") anim_player.switch_animation("run_left");
		step_x = -step;
	}
}


void Player::move_right(double step)
{
	if (sprite_player.getPosition().x < borders.max_x) {
		if (anim_player.get_current_animation_name() != "run_right") anim_player.switch_animation("run_right"); 
		step_x = step;
	}
}


void Player::update(Time const& delta_time)
{
	if (!dead) anim_player.update(delta_time);

	if (step_x == 0 and step_y == 0) anim_player.switch_animation("player_static");


	time_update += delta_time;

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


void Player::set_dead(bool player_dead)
{
	dead = player_dead;
}


bool Player::get_dead() const
{
	return dead;
}


Sprite& Player::get_player()
{
	return sprite_player;
}
