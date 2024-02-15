#include "Game.h"


Game::Game()
{
	int pos = static_cast<int>(double(win_width - win_height) / 2.0);

	maps.setSize(Vector2f(win_height, win_height));
	maps.setPosition(Vector2f(pos, 0));
	maps.setFillColor(Color::Black);

	background_sprite.setTexture(AssetManager::get_texture("Resourses/background_image.png"));

	timer = 300; // 5 минут
	lives = 3; // жизни игрока
	
	game_font.loadFromFile("Resourses/weekend.ttf");

	playground_text.setFont(game_font);
	playground_text.setCharacterSize(win_height / 20);
	playground_text.setFillColor(Color::White);
	playground_text.setString(L"Карта");

	timer_text.setFont(game_font);
	timer_text.setCharacterSize(win_height / 20);
	timer_text.setFillColor(Color::White);
	timer_string << timer;
	timer_text.setString(L"Время: " + timer_string.str() + " ");
	timer_text.setPosition(win_width - timer_text.getGlobalBounds().width, 0);

	lives_sprite.setTexture(AssetManager::get_texture("Resourses/lives.png"));
	lives_sprite.scale(0.05f, 0.05f);
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().height));
}


void Game::update(Time const& delta_time)
{
	timer -= delta_time.asSeconds();

	timer_string.str("");
	timer_string << timer;
	timer_text.setString(L"Время: " + timer_string.str() + " ");
}

RectangleShape& Game::get_maps() {
	return maps;
}

void Game::decrease_lives() 
{
	lives_sprite.setTextureRect(IntRect(0, 0, lives_sprite.getLocalBounds().width / lives * (lives - 1), lives_sprite.getLocalBounds().height));
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().height));
	lives -= 1;
}


void Game::kill()
{
	lives = 0;
	
	lives_sprite.setTextureRect(IntRect(0, 0, 0, 0));
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().height));
}

void Game::update_playground(const string& playground_name)
{
	playground_text.setString(playground_name);
}