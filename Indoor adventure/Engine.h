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

	vector<string> name = { "������", "�����", "����", "�������� �����" };
	Color text_color = Color::Red;
	Color board_color = Color::Black;
	Game my_game = Game(*window, 12, 30, name, text_color, board_color, 3);

	// �������� ������
	Player* player = new Player_static(my_game.get_maps());
	Time player_time;
	Sprite player_sprite;

	Gun my_gun = Gun(*window,player->get_player());

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
