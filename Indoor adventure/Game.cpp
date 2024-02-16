#include "Game.h"

Game::Game()
{
	int pos = static_cast<int>(double(win_width - win_height) / 2.0);
	int font_size = win_height / 20;

	maps.setSize(Vector2f(win_height, win_height));
	maps.setPosition(Vector2f(pos, 0));
	maps.setFillColor(Color::Black);

	background_sprite.setTexture(AssetManager::get_texture("Resourses/background_image.png"));

	end_game = false;
	timer = 300; // 5 минут
	lives = 3; // жизни игрока
	score = 0;
	
	game_font.loadFromFile("Resourses/weekend.ttf");

	playground_name = "Playground";
	playground_text.setFont(game_font);
	playground_text.setCharacterSize(font_size);
	playground_text.setFillColor(Color::White);
	playground_text.setString(String::fromUtf32(playground_name.begin(), playground_name.end()));

	score_text.setFont(game_font);
	score_text.setCharacterSize(font_size);
	score_text.setFillColor(Color::White);
	score_string << score;
	score_text.setString(L"Bonuses: " + score_string.str() + " ");
	score_text.setPosition(win_width - score_text.getGlobalBounds().width, 0);

	timer_text.setFont(game_font);
	timer_text.setCharacterSize(font_size);
	timer_text.setFillColor(Color::White);
	timer_string << timer;
	timer_text.setString(L"Time: " + timer_string.str() + " ");
	timer_text.setPosition(win_width - timer_text.getGlobalBounds().width, score_text.getGlobalBounds().top + score_text.getGlobalBounds().height);

	
	lives_sprite.setTexture(AssetManager::get_texture("Resourses/lives.png"));
	lives_sprite.scale(0.05f, 0.05f);
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().top + timer_text.getGlobalBounds().height));

	skulls_sprite.setTexture(AssetManager::get_texture("Resourses/sculls.png"));
	skulls_sprite.scale(0.05f, 0.05f);
	skulls_sprite.setPosition(Vector2f(win_width - skulls_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().top + timer_text.getGlobalBounds().height));
}


void Game::update(Time const& delta_time)
{
	if (!end_game)
	{
		timer -= delta_time.asSeconds();

		timer_string.str("");
		timer_string << int(timer);
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

void Game::restart()
{
	end_game = false;
	timer = 300; // 5 минут
	lives = 3; // жизни игрока
	score = 0;

	score_string.str("");
	score_string << score;
	score_text.setString(L"Bonuses: " + score_string.str() + " ");
	score_text.setPosition(win_width - score_text.getGlobalBounds().width, 0);

	timer_string.str("");
	timer_string << timer;
	timer_text.setString(L"Time: " + timer_string.str() + " ");
	timer_text.setPosition(win_width - timer_text.getGlobalBounds().width, score_text.getGlobalBounds().top + score_text.getGlobalBounds().height);

	lives_sprite.setTextureRect(IntRect(0, 0, 3000, lives_sprite.getLocalBounds().height));
	lives_sprite.setPosition(Vector2f(win_width - lives_sprite.getGlobalBounds().width, timer_text.getGlobalBounds().top + timer_text.getGlobalBounds().height));
}

bool Game::get_end_game() {
	return end_game;
}

void Game::set_end_game(bool end_game) {
	this->end_game = end_game;
}

int Game::get_score() {
	return score;
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

void Game::update_score()
{
	score += 1;
	score_string.str("");
	score_string << score;
	score_text.setString(L"Bonuses: " + score_string.str() + " ");
	score_text.setPosition(win_width - score_text.getGlobalBounds().width, 0);
}

void Game::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background_sprite);
	target.draw(score_text);
	target.draw(timer_text);
	if (!end_game)
		target.draw(lives_sprite);
	else
		target.draw(skulls_sprite);
	target.draw(maps);
	target.draw(playground_text);
}