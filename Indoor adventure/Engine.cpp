#include "Engine.h"


void Engine::input()
{
	Event event_play;
	my_gun.update_bullet_pos(player->get_player());

	while (window->pollEvent(event_play)) {
		if (event_play.key.code == Keyboard::Escape) {
			window->close();
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
			case Keyboard::Left: {player->set_step_x(); break; }
			case Keyboard::Right: {player->set_step_x(); break; }
			default: break;
			}
		}

		if (event_play.type == Event::MouseMoved) {
			my_gun.update_mouse_pos(Mouse::getPosition(*window));
		}

		if (event_play.type == Event::MouseButtonPressed) {
			if (event_play.key.code == Mouse::Left) {
				if (!my_gun.check_shoot())
					my_gun.shoot();
			}
		}
	}
}


void Engine::update(Time const& delta_time)
{
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
	my_gun.draw(*window);
	auto draw_player = player->get_player();
	window->draw(draw_player);
	window->display();
}


Engine::Engine()
{
	icon.loadFromFile("Resourses/icon.png");
	window->setIcon(200, 200, icon.getPixelsPtr());

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
