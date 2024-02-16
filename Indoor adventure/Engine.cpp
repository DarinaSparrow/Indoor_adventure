#include "Engine.h"


void Engine::input()
{
	Event event_play;
	my_gun.update_bullet_pos(player->get_player());

	while (window->pollEvent(event_play)) {
		if (event_play.key.code == Keyboard::Escape) {
			window->close();
		}

		if (event_play.key.code == Keyboard::Enter) {
			restart();
		}

		if (event_play.type == event_play.Closed) {
			window->close();
		}

		if (!player->get_dead()) {
			if (event_play.type == Event::KeyPressed) {
				if (!player->get_slide()) {
					switch (event_play.key.code)
					{
					case Keyboard::Up: { player->move_up(); mus_and_sound.play(1); break; }
					case Keyboard::Down: { player->move_down(); mus_and_sound.play(1); break; }
					case Keyboard::Left: { player->move_left(); mus_and_sound.play(1); break; }
					case Keyboard::Right: { player->move_right(); mus_and_sound.play(1); break; }
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
					if (!my_gun.check_shoot() and player->get_fire())
					{
						my_gun.shoot();
						mus_and_sound.play_ignore(3);
					}
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
	mus_and_sound.play(0);

	if (game.get_end_game() && game.get_score() != bonuses.GetTotal())
		end.result(false, game.get_score());
	else if (game.get_score() == bonuses.GetTotal())
	{
		game.set_end_game(true);
		end.result(true, game.get_score());
	}
	else
	{
		if (playgrounds.GetNameOfCurrentMap() != game.get_playground_name())
			game.update_playground(playgrounds.GetNameOfCurrentMap());

		player->set_dead(game.get_end_game());

		game.update(delta_time);
		playgrounds.CheckTheTransitionBetweenMaps(player, my_gun);
		playgrounds.ChechCollisionWithPlayer(my_gun, *player, game);
		playgrounds.ChechCollisionWithMobs(my_gun);
		playgrounds.ChechCollisionWithWalls(*player, game);
		player->catch_bonus(my_gun, game, bonuses);
		player->update(delta_time);
		playgrounds.ChechCollisionWithObstacles(*player);
		if (player->get_fire())	my_gun.update(delta_time);
	}
}


void Engine::draw()
{
	window->clear();
	window->draw(game);
	playgrounds.Draw(window);
	bonuses.Draw(window);
	if (player->get_fire())	my_gun.draw(*window);
	if (player->get_visible()) {
		auto draw_player = player->get_player();
		window->draw(draw_player);
	}
	if (game.get_end_game())
		window->draw(end);
	window->display();
}

void Engine::restart()
{
	game.restart();
	playgrounds.Restart(bonuses, player);
	bonuses.Restart();
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
	playgrounds.GenerateBonuses(bonuses);
	playgrounds.GenerateCoordinatesOfPlayer(player);
	while (window->isOpen()) {
		Time dt = clock.restart();

		input();
		update(dt);
		draw();
	}
}