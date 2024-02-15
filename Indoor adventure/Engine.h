#pragma once
#include "header.h"
#include "AssetManager.h"
#include "Animator.h"
#include "Player.h"
#include "Game.h"
#include "Maps.h"
#include "Gun.h"
#include "GameSound.h"
#include "End.h"
#include "Bonus.h"


class Engine
{
private:
	AssetManager manager;

	unique_ptr<RenderWindow> window = make_unique<RenderWindow>(VideoMode(win_width, win_height),
		"Indoor Adventure", Style::Default);

	Image icon;

	Game game;
	GameSound mus_and_sound;

	Player* player = new Player_static(game.get_maps(), Vector2f(win_width / 2, 650), mus_and_sound, "static", Vector2f(0,0));

	Gun my_gun = Gun(*window,player->get_player(), game.get_maps());

	Maps playgrounds;

	End end;
	Bonus bonuses;

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

