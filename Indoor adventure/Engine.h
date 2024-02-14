#pragma once
#include "header.h"
#include "AssertManager.h"
#include "Animator.h"
#include "Player.h"
#include "Game.h"
#include "Maps.h"
#include "Gun.h"


class Engine
{
private:
	AssertManager manager;

	unique_ptr<RenderWindow> window = make_unique<RenderWindow>(VideoMode(win_width, win_height),
		"Indoor Adventure", Style::Default);

	RectangleShape background = RectangleShape(Vector2f(win_width, win_height));

	vector<string> name = { "таймер", "жизни", "очки", "название карты" };
	Color text_color = Color::Red;
	Color board_color = Color::Black;
	Game game;

	// Анимация игрока
	Player* player = new Player_static(game.get_maps());
	Time player_time;
	Sprite player_sprite;

	Gun my_gun = Gun(*window,player->get_player());

	Maps playgrounds;

	void input();
	void update(Time const& delta_time);
	void draw();

public:
	Engine();

	~Engine() {
		delete player;
	}

	void run();
};

