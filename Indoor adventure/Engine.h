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

	
	Game game;

	// Анимация игрока
	Player* player = new Player_static(game.get_maps());
	Time player_time;
	

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

