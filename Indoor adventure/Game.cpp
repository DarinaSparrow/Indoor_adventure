#include "Game.h"


Game::Game(RenderWindow& window, int size_font, int step, vector<string>& name, Color text_color, Color border_color, int border_size)
	:labels_step(step), font_size(size_font), my_window(window), text_color(text_color), border_color(border_color), border_size(border_size)
{
	int pos = static_cast<int>(double(S_W - S_H) / 2.0);

	maps.setSize(Vector2f(S_H, S_H));
	maps.setPosition(Vector2f(pos, 0));
	maps.setFillColor(Color::Black);

	//auto it = name.begin();

	//setInitText(timer, )
}


void Game::update(Time const& delta_time)
{

}

RectangleShape& Game::get_maps()
{
	return maps;
}


void Game::draw()
{
	my_window.draw(maps);
}


void Game::setInitText(Text& text, const String& str, float xpos, float ypos) const
{
	text.setFont(AssertManager::get_font("Resourses/Kenney Blocks.ttf"));
	text.setFillColor(text_color);
	text.setString(str);
	text.setCharacterSize(font_size);
	text.setOutlineThickness(border_size);
	text.setOutlineColor(border_color);
	text.setPosition(xpos, ypos);
}
