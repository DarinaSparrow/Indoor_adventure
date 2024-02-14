#pragma once
#include "header.h"
#include "Animator.h"


// Класс "Игрок", реализует перемещение, коллизию и анимацию модельки игрока
class Player
{
private:
	// Структура для обозначения границ перемещения пользователя
	struct Borders
	{
		double x; 
		double y;
		double max_x;
		double max_y;
	};


	Sprite sprite_player;
	Animator anim_player = Animator(sprite_player);

	double step_x = 0.0;
	double step_y = 0.0;

	Borders borders{ 0 };

	Time time_update;
	bool dead = false;

public:
	Player(RenderWindow& window, Vector2f my_pos = Vector2f(S_W / 2, 650), double time = 0.3,
		Vector2i sprite_size = Vector2i(192, 256))
	{
		sprite_player.setPosition(my_pos.x, my_pos.y);

		auto& idle_static = anim_player.create_animation("player_static", "Resourses/player.png", seconds(time), true);
		idle_static.AddFrames(Vector2i(0, 0), sprite_size, 1, 1);

		auto& idle_run_right = anim_player.create_animation("run_right", "Resourses/player_run_right.png",
			seconds(time), true);
		idle_run_right.AddFrames(Vector2i(0, 0), sprite_size, 3, 1);

		auto& idle_run_left = anim_player.create_animation("run_left", "Resourses/player_run_left.png",
			seconds(time), true);
		idle_run_left.AddFrames(Vector2i(0, 0), sprite_size, 3, 1);


		borders.max_x = static_cast<double>(window.getSize().x);
		borders.max_y = static_cast<double>(window.getSize().y);

		sprite_player.scale(Vector2f(0.5,0.5));
	}

	void set_step_x(double x);
	void set_step_y(double y);

	void move_up(double step = 5.0);
	void move_down(double step = 5.0);
	void move_left(double step = 5.0);
	void move_right(double step = 5.0);

	void update(Time const& delta_time);

	void set_borders_player(double x, double y, double max_x, double max_y);

	void set_dead(bool player_dead);

	bool get_dead() const;

	Sprite& get_player();
};