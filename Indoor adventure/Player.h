#pragma once
#include "header.h"
#include "Animator.h"
#include "GameSound.h"
#include <tuple>


class Player
{
private:
	RectangleShape border;
	GameSound& game_sound;

	struct Borders
	{
		double x; 
		double y;
		double max_x;
		double max_y;
	};

	Sprite sprite_player;
	Animator anim_player = Animator(sprite_player);

	double step_x;
	double step_y;

	Borders borders{ 0 };
	Time time_update;

protected:
	bool dead;
	bool visible;
	bool slide;

public:
	Player(RectangleShape& borders_zone, Vector2f my_pos, GameSound& my_game_sound, string anim = "static", Vector2f steps = Vector2f(0,0)) 
		: border(borders_zone), game_sound(my_game_sound), step_x(steps.x), step_y(steps.y)
	{
		sprite_player.setPosition(my_pos.x, my_pos.y);
		
		auto& idle_static = anim_player.create_animation("static", "Resourses/down.png",
			seconds(0.3), true);
		idle_static.AddFrames(Vector2i(0, 0), Vector2i(50, 80), 1, 1);

		auto& idle_run_down = anim_player.create_animation("run_down", "Resourses/down.png",
			seconds(0.3), true);
		idle_run_down.AddFrames(Vector2i(0, 0), Vector2i(50, 80), 3, 1);

		auto& idle_run_up = anim_player.create_animation("run_up", "Resourses/up.png",
			seconds(0.3), true);
		idle_run_up.AddFrames(Vector2i(0, 0), Vector2i(50, 80), 3, 1);

		auto& idle_run_right = anim_player.create_animation("run_right", "Resourses/right.png",
			seconds(0.3), true);
		idle_run_right.AddFrames(Vector2i(0, 0), Vector2i(50, 80), 3, 1);

		auto& idle_run_left = anim_player.create_animation("run_left", "Resourses/left.png",
			seconds(0.3), true);
		idle_run_left.AddFrames(Vector2i(0, 0), Vector2i(50, 80), 3, 1);


		borders.x = static_cast<double>(borders_zone.getPosition().x);
		borders.y = static_cast<double>(borders_zone.getPosition().y);

		borders.max_x = static_cast<double>(borders_zone.getPosition().x + borders_zone.getSize().x);
		borders.max_y = static_cast<double>(borders_zone.getPosition().y + borders_zone.getSize().y);


		dead = false;
		visible = true;
		slide = false;

		sprite_player.scale(Vector2f(1.5, 1.5));

		anim_player.switch_animation(anim);
	}

	virtual void set_dead(bool fl) = 0;
	virtual bool get_dead() const = 0;

	virtual void set_visible(bool fl) = 0;
	virtual bool get_visible() = 0;

	virtual void set_slide(bool fl) = 0;
	virtual bool get_slide() = 0;

	virtual tuple<bool, bool, bool> get_params() = 0;

	void set_step_x(double x = 0.0);
	void set_step_y(double y = 0.0);

	Vector2f get_steps();


	void move_up(double step = 5.0);
	void move_down(double step = 5.0);
	void move_left(double step = 5.0);
	void move_right(double step = 5.0);

	void update(Time const& delta_time);

	void set_borders_player(double x, double y, double max_x, double max_y);

	Sprite& get_player();
	RectangleShape& get_bords();
	GameSound& get_sound();
	string get_cur_anim();
};


class Player_static: public Player
{
public:
	Player_static(RectangleShape& borders_zone, Vector2f my_pos, GameSound& my_game_sound, string anim, Vector2f steps) 
		:Player(borders_zone, my_pos, my_game_sound, anim, steps)
	{
		dead = false;
		visible = true;
		slide = false;
	}

	void set_dead(bool fl) override;
	bool get_dead() const override;

	void set_visible(bool fl) override;
	bool get_visible() override;

	void set_slide(bool fl) override;
	bool get_slide() override;

	tuple<bool, bool, bool> get_params() override;
};


class Player_vector : public Player
{
public:
	Player_vector(RectangleShape& borders_zone, Vector2f my_pos, GameSound& my_game_sound, string anim, Vector2f steps)
		:Player(borders_zone, my_pos, my_game_sound, anim, steps)
	{
		dead = false;
		visible = true;
		slide = true;
	}

	void set_dead(bool fl) override;
	bool get_dead() const override;

	void set_visible(bool fl) override;
	bool get_visible() override;

	void set_slide(bool fl) override;
	bool get_slide() override;

	tuple<bool, bool, bool> get_params() override;
};


class Player_invisible : public Player
{
public:
	Player_invisible(RectangleShape& borders_zone, Vector2f my_pos, GameSound& my_game_sound, string anim, Vector2f steps)
		:Player(borders_zone, my_pos, my_game_sound, anim, steps)
	{
		dead = false;
		visible = false;
		slide = false;
	}

	void set_dead(bool fl) override;
	bool get_dead() const override;

	void set_visible(bool fl) override;
	bool get_visible() override;

	void set_slide(bool fl) override;
	bool get_slide() override;

	tuple<bool, bool, bool> get_params() override;
};


class Player_danger_zone : public Player
{
public:
	Player_danger_zone(RectangleShape& borders_zone, Vector2f my_pos, GameSound& my_game_sound, string anim, Vector2f steps)
		:Player(borders_zone, my_pos, my_game_sound, anim, steps)
	{
		dead = false;
		visible = true;
		slide = false;
	}

	void set_dead(bool fl) override;
	bool get_dead() const override;

	void set_visible(bool fl) override;
	bool get_visible() override;

	void set_slide(bool fl) override;
	bool get_slide() override;

	tuple<bool, bool, bool> get_params() override;
};