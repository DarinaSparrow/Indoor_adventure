#pragma once
#include "header.h"
#include "Animator.h"
#include "chrono"
#include <vector>


// Класс для реализации интерефейса
// Он отображает все кнопки и прочие элементы, а также реализует взаимодействие
// Частью этого класса является выделение места под игровое поле
// Возможно есть реализация по-лучше 
class Game
{
private:
	int labels_step;
	vector<Text> text_labels;

	Color text_color;
	int font_size;

	Color border_color;
	int border_size;

	RenderWindow& my_window;

	RectangleShape maps;
	RectangleShape timer;
	RectangleShape health;
	RectangleShape score;
	RectangleShape picture_of_player;
	RectangleShape title_of_map;
	RectangleShape description_of_map;
	RectangleShape picture_of_map;

	Sprite sprite_button_restart;
	Animator anim_button_restart = Animator(sprite_button_restart);

	Time time_update;

	void setInitText(Text& text, const String& str, float xpos, float ypos) const;

public:
	Game(RenderWindow& window, int size_font, int step, vector<string>& name, Color text_color, Color border_color, int border_size);

	void update(Time const& delta_time);

	void draw();
};