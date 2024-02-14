#pragma once
#include "header.h"
#include "AssertManager.h"
#include "Animator.h"
#include "Player.h"
#include "Game.h"
#include "Maps.h"

//  ласс представл€ющий из себ€ основной движок игры
class Engine
{
private:
	AssertManager manager;

	unique_ptr<RenderWindow> window = make_unique<RenderWindow>(VideoMode(S_W, S_H),
		"Indoor Adventure", Style::Default);

	RectangleShape background = RectangleShape(Vector2f(S_W, S_H));

	vector<string> name = { "таймер", "жизни", "очки", "название карты" };
	Color text_color = Color::Red;
	Color board_color = Color::Black;
	Game my_game = Game(*window, 12, 30, name, text_color, board_color, 3);

	// јнимаци€ игрока
	Player player = Player(*window);
	Time player_time;
	Sprite player_sprite;

	void input();
	void update(Time const& delta_time);
	void draw();

public:
	Engine();
	void run();
};

