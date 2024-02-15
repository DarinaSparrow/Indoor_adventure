#include "Game.h"

Game::Game()
{
	int pos = static_cast<int>(double(win_width - win_height) / 2.0);

	maps.setSize(Vector2f(win_height, win_height));
	maps.setPosition(Vector2f(pos, 0));
	maps.setFillColor(Color::Black);

	background_sprite.setTexture(AssertManager::get_texture("Resourses/background_image.png"));

	end_game = false;
	timer = 10; // 5 минут
	lives = 3; // жизни игрока
	
	game_font.loadFromFile("Resourses/weekend.ttf");

	playground_name = "Playground";
	playground_text.setFont(game_font);
	playground_text.setCharacterSize(win_height / 20);
	playground_text.setFillColor(Color::White);
	playground_text.setString(String::fromUtf32(playground_name.begin(), playground_name.end()));

	timer_text.setFont(game_font);
	timer_text.setCharacterSize(win_height / 20);
	timer_text.setFillColor(Color::White);
	timer_string << timer;
	timer_text.setString(L"Time: " + timer_string.str() + " ");
	timer_text.setPosition(win_width - timer_text.getGlobalBounds().width, 0);

	lives_sprite.setTexture(AssertManager::get_texture("Resourses/lives.png"));
	lives_sprite.scale(0.05f, 0.05f);
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().top + timer_text.getGlobalBounds().height));

	skulls_sprite.setTexture(AssertManager::get_texture("Resourses/sculls.png"));
	skulls_sprite.scale(0.05f, 0.05f);
	skulls_sprite.setPosition(Vector2f(win_width - skulls_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().top + timer_text.getGlobalBounds().height));
}


void Game::update(Time const& delta_time)
{
	if (!end_game)
	{
		timer -= delta_time.asSeconds();

		timer_string.str("");
		timer_string << timer;
		timer_text.setString(L"Time: " + timer_string.str() + " ");
	}

	if ((lives == 0 || timer <= 0) && !end_game) {
		end_game = true;

		if (timer <= 0)
		{
			timer_string.str("");
			timer_string << 0;
			timer_text.setString(L"Time: " + timer_string.str() + " ");
		}
	}
	
	
}

RectangleShape& Game::get_maps() {
	return maps;
}

bool Game::get_end_game() {
	return end_game;
}

void Game::set_end_game(bool end_game) {
	this->end_game = end_game;
}

string Game::get_playground_name() {
	return playground_name;
}

void Game::decrease_lives() 
{
	lives_sprite.setTextureRect(IntRect(0, 0, lives_sprite.getLocalBounds().width / lives * (lives - 1), lives_sprite.getLocalBounds().height));
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().top + timer_text.getGlobalBounds().height));
	lives -= 1;
}


void Game::kill()
{
	lives = 0;
	lives_sprite.setTextureRect(IntRect(0, 0, 0, 0));
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().top + timer_text.getGlobalBounds().height));
}

void Game::update_playground(const string& playground_name) {
	this->playground_name = playground_name;
	playground_text.setString(String::fromUtf8(this->playground_name.begin(), this->playground_name.end()));
}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background_sprite);
	target.draw(timer_text);
	if (!end_game)
		target.draw(lives_sprite);
	else
		target.draw(skulls_sprite);
	target.draw(maps);
	target.draw(playground_text);
}