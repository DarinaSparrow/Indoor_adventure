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

		if (!player->get_dead()) {
			if (event_play.type == Event::KeyPressed) {
				if (!player->get_slide()) {
					switch (event_play.key.code)
					{
					case Keyboard::Up: { player->move_up(); break; }
					case Keyboard::Down: { player->move_down(); break; }
					case Keyboard::Left: { player->move_left(); break; }
					case Keyboard::Right: { player->move_right(); break; }
					default: break;
					}
				}
				else {
					switch (event_play.key.code)
					{
					case Keyboard::Up: { player->set_step_x(); player->move_up(); break; }
					case Keyboard::Down: { player->set_step_x(); player->move_down(); break; }
					case Keyboard::Left: { player->set_step_y(); player->move_left(); break; }
					case Keyboard::Right: { player->set_step_y();  player->move_right(); break; }
					default: break;
					}
				}
			}

			if (event_play.type == Event::KeyReleased and !player->get_slide()) {
				switch (event_play.key.code)
				{
				case Keyboard::Up: { player->set_step_y(); break; }
				case Keyboard::Down: { player->set_step_y(); break; }
				case Keyboard::Left: { player->set_step_x(); break; }
				case Keyboard::Right: { player->set_step_x(); break; }
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
		else {
			player->set_step_x();
			player->set_step_y();
		}
	}
}



void Engine::update(Time const& delta_time)
{
	if (game.get_end_game())
		end.result(0, game.get_score());
	else if (game.get_score() == bonuses.GetTotal())
		end.result(1, game.get_score());
	else
	{
		if (playgrounds.GetNameOfCurrentMap() != game.get_playground_name())
			game.update_playground(playgrounds.GetNameOfCurrentMap());

		player->set_dead(game.get_end_game());

		game.update(delta_time);
		playgrounds.CheckTheTransitionBetweenMaps(player);
		playgrounds.ChechCollisionWithPlayer(my_gun, *player, game);
		playgrounds.ChechCollisionWithMobs(my_gun);
		playgrounds.ChechCollisionWithWalls(*player, game);
		player->update(delta_time);
		playgrounds.ChechCollisionWithObstacles(*player);
		my_gun.update(delta_time);
	}
}


void Engine::draw()
{
	window->clear();
	window->draw(game);
	playgrounds.Draw(window);
	bonuses.Draw(window);
	my_gun.draw(*window);
	if (player->get_visible()) {
		auto draw_player = player->get_player();
		window->draw(draw_player);
	}
	if (game.get_end_game())
		window->draw(end);
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
	playgrounds.InstallTheInitialMap(player);
	playgrounds.GenerateBonuses(bonuses);
	playgrounds.GenerateCoordinatesOfPlayer(player);
	while (window->isOpen()) {
		Time dt = clock.restart();

		input();
		update(dt);
		draw();
	}
}
