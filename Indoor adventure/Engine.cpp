#include "Engine.h"


void Engine::input()
{
	Event event_play;
	
	while (window->pollEvent(event_play)) {
		if (event_play.key.code == Keyboard::Escape) {
		}

		if (event_play.type == event_play.Closed) {
			window->close();
		}

		if (event_play.type == Event::KeyPressed) {
			switch (event_play.key.code)
			{
			case Keyboard::Up: {player->move_up(); break; }
			case Keyboard::Down: {player->move_down(); break; }
			case Keyboard::Left: {player->move_left(); break;}
			case Keyboard::Right: {player->move_right(); break; }
			default: break;
			}
		}

		if (event_play.type == Event::KeyReleased) {
			switch (event_play.key.code)
			{
			case Keyboard::Up: {player->set_step_y(); break; }
			case Keyboard::Down: {player->set_step_y(); break; }
			case Keyboard::Left: {player->set_step_x(); game.set_end_game(false); break; }
			case Keyboard::Right: {player->set_step_x(); game.set_end_game(true); break; }
			default: break;
			}
		}

		if (event_play.type == Event::MouseMoved) {
				my_gun.set_x(Mouse::getPosition(*window).x);
				my_gun.set_y(Mouse::getPosition(*window).y);
		}
	}
}


void Engine::update(Time const& delta_time)
{
	if (playgrounds.GetNameOfCurrentMap() != game.get_playground_name())
		game.update_playground(playgrounds.GetNameOfCurrentMap());

	game.update(delta_time);
	player->update(delta_time);
	my_gun.update(delta_time);
	player_time += delta_time;
	if (player_time > microseconds(3)) {
		player_time = milliseconds(0);
	}
}


void Engine::draw()
{
	window->clear();

	window->draw(game);
	playgrounds.Draw(window);
	auto draw_player = player->get_player();
	window->draw(draw_player);
	auto draw_aim = my_gun.get_aim();
	auto draw_bullet = my_gun.get_bullet();
	window->draw(draw_aim);
	window->draw(draw_bullet);
	
	if (game.get_end_game())
		window->draw(end);

	window->display();
}


Engine::Engine()
{
	window->setVerticalSyncEnabled(true);
}


void Engine::run()
{
	Clock clock;
	while (window->isOpen()) {
		Time dt = clock.restart();

		input();
		update(dt);
		draw();
	}
}
