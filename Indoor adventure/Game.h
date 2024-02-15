#pragma once
#include "AssetManager.h"
#include "chrono"


// Класс для реализации интерефейса
// Он отображает все кнопки и прочие элементы, а также реализует взаимодействие
// Частью этого класса является выделение места под игровое поле
// Возможно есть реализация по-лучше 
class Game : public Drawable, public Transformable
{
private:
	RectangleShape maps;

	Sprite background_sprite;
	Sprite lives_sprite;
	Sprite skulls_sprite;

	Font game_font;
	Text timer_text;
	ostringstream timer_string;

	Text playground_text;

	string playground_name;
	float timer;
	int lives;

	bool end_game;

public:
	Game();
	RectangleShape& get_maps();

	void restart();

	bool get_end_game();
	void set_end_game(bool end_game);
	string get_playground_name();

	void decrease_lives();

	void kill();
	void update_playground(const string& playground_name);

	void update(Time const& delta_time);

	virtual void draw(RenderTarget& target, RenderStates states) const;
};