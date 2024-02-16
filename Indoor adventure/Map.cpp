#include "Map.h"

void Map::SetCoordinates(double x1, double y1, double x2, double y2)
{
	playground.setPosition(x1, y1);
	playground.setSize(Vector2f(x2 - x1, y2 - y1));

	borders.x1 = x1;
	borders.x2 = x2;
	borders.y1 = y1;
	borders.y2 = y2;
}

void Map::SetLimits(bool limits)
{
	this->limits = limits;
}

string Map::GetNameOfTheMap() { return name; }

double Map::GetX1() { return borders.x1; }

double Map::GetX2() { return borders.x2; }

double Map::GetY1() { return borders.y1; }

double Map::GetY2() { return borders.y2; }

bool Map::ÑheckPersonLocationOnMap(double current_x, double current_y)
{
	if (limits)
	{
		if ((current_x >= borders.x1) && (current_x <= borders.x2) && (current_y >= borders.y1) && (current_y <= borders.y2)) return true;
		else return false;
	}
	else
	{
		if ((current_x > borders.x1) && (current_x < borders.x2) && (current_y > borders.y1) && (current_y < borders.y2)) return true;
		else return false;
	}
}

void InvisibleMap::GenerateComplications() { ; }

void InvisibleMap::GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated)
{
	double x, y, size;
	bool fixation;

	size = 50;

	for (int i = first_no_generated; i < first_no_generated + count_of_bonuses; i++)
	{
		do
		{
			x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
			y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

			int j = first_no_generated;
			fixation = true;
			while ((j < i) && (fixation))
			{
				if ((bonuses.GetCoordinateX(j) > (x - size - 5)) && (bonuses.GetCoordinateX(j) < (x + size + 5)) && (bonuses.GetCoordinateY(j) > (y - size - 5)) && (bonuses.GetCoordinateY(j) < (y + size + 5))) fixation = false;
				else j++;
			}

		} while (!fixation);

		bonuses.SetSpriteCoordinates(i, x, y);
	}

	first_no_generated += count_of_bonuses;
}

void InvisibleMap::GenerateCoordinatesOfPlayer(Player* player)
{
	double x, y, size_x, size_y;

	size_x = 75;
	size_y = 120;

	x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size_x - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
	y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size_y - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

	player->set_position(x, y);
}

void InvisibleMap::RedefinePlayer(Player*& player, Vector2f steps)
{
	Player* new_player = new Player_invisible(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), steps);
	delete player;
	player = new_player;
}

void InvisibleMap::Draw(unique_ptr<RenderWindow>& window)
{
	window->draw(playground);
}

void InvisibleMap::CheckCollsisionWithMobs(Gun& obj) { ; }

void InvisibleMap::ChechCollisionWithWalls(Player& player, Game& rules) { ; }

void InvisibleMap::ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) { ; }

void InvisibleMap::ChechCollisionWithObstacles(Player& player) { ; }

void MapWithMobs::GenerateComplications()
{
	double x, y, size_x, size_y;
	bool fixation;

	srand(time(NULL));

	count_of_enemies = rand() % (7 - 5 + 1) + 5;

	size_x = 57;
	size_y = 80;

	enemies = new Mob*[count_of_enemies];
	for (int i = 0; i < count_of_enemies; i++)
	{
		enemies[i] = new Mob;

		do
		{
			x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size_x - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
			y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size_y - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

			int j = 0;
			fixation = true;
			while ((j < i) && (fixation))
			{
				if ((enemies[j]->x1 > (x - size_x - 50)) && (enemies[j]->x1 < (x + size_x + 50)) && (enemies[j]->y1 > (y - size_y - 50)) && (enemies[j]->y1 < (y + size_y + 50))) fixation = false;
				else j++;
			}

		} while (!fixation);

		enemies[i]->mob.setPosition(x, y);
		enemies[i]->mob.setSize(Vector2f(size_x, size_y));
		enemies[i]->mob.setTexture(&enemies_texture);

		enemies[i]->x1 = x;
		enemies[i]->x2 = x + size_x;
		enemies[i]->y1 = y;
		enemies[i]->y2 = y + size_y;

		//enemies[i]->mob.setScale(Vector2f(1.0, 1.0));
	}
}

void MapWithMobs::GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated)
{
	double x, y, size_1, size_2, size_3;
	bool fixation;

	size_1 = 50;
	size_2 = 57;
	size_3 = 80;

	for (int i = first_no_generated; i < first_no_generated + count_of_bonuses; i++)
	{
		do
		{
			x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size_1 - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
			y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size_1 - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

			int j = first_no_generated;
			fixation = true;
			while ((j < i) && (fixation))
			{
				if ((bonuses.GetCoordinateX(j) > (x - size_1 - 5)) && (bonuses.GetCoordinateX(j) < (x + size_1 + 5)) && (bonuses.GetCoordinateY(j) > (y - size_1 - 5)) && (bonuses.GetCoordinateY(j) < (y + size_1 + 5))) fixation = false;
				else j++;
			}

			if (fixation)
			{
				int k = 0;
				fixation = true;
				while ((k < count_of_enemies) && (fixation))
				{
					if ((x > (enemies[k]->x1 - size_1 - 5)) && (x < (enemies[k]->x1 + size_2 + 5)) && (y > (enemies[k]->y1 - size_1 - 5)) && (y < (enemies[k]->y1 + size_3 + 5))) fixation = false;
					else k++;
				}
			}

		} while (!fixation);

		bonuses.SetSpriteCoordinates(i, x, y);
	}

	first_no_generated += count_of_bonuses;
}

void MapWithMobs::GenerateCoordinatesOfPlayer(Player* player) // äîïèñàòü
{
	double x, y, size_1, size_2, size_3, size_4;
	bool fixation;

	size_1 = 75;
	size_2 = 120;
	size_3 = 57;
	size_4 = 80;

	do
	{
		x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size_1 - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
		y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size_2 - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

		int i = 0;
		fixation = true;
		while ((i < count_of_enemies) && (fixation))
		{
			if ((enemies[i]->x1 > (x - size_3 - 5)) && (enemies[i]->x1 < (x + size_1 + 5)) && (enemies[i]->y1 > (y - size_4 - 5)) && (enemies[i]->y1 < (y + size_2 + 5))) fixation = false;
			else i++;
		}
	} while (!fixation);

	player->set_position(x, y);
}

void MapWithMobs::RedefinePlayer(Player*& player, Vector2f steps)
{
	Player* new_player = new Player_danger_zone(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), steps);
	delete player;
	player = new_player;
}

void MapWithMobs::Draw(unique_ptr<RenderWindow>& window)
{
	window->draw(playground);
	for (int i = 0; i < count_of_enemies; i++) window->draw(enemies[i]->mob);
}

void MapWithMobs::CheckCollsisionWithMobs(Gun& obj)
{
	for (int i = 0; i < count_of_enemies; i++) {
		if (enemies[i]->mob.getGlobalBounds().contains(Vector2f(obj.get_bul().getPosition().x + obj.get_bul().getGlobalBounds().width / 2.0, 
			obj.get_bul().getPosition().y + obj.get_bul().getGlobalBounds().height / 2.0))) {
			enemies[i]->mob.setPosition(Vector2f(-enemies[i]->mob.getPosition().x, -enemies[i]->mob.getPosition().y));
			obj.refresh_bul();
			
		}
	}
}

void MapWithMobs::ChechCollisionWithWalls(Player& player, Game& rules) { ; }

void MapWithMobs::ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules)
{
	for (int i = 0; i < count_of_enemies; i++) {
		if (enemies[i]->mob.getGlobalBounds().contains(Vector2f(obj.get_bul().getPosition().x + obj.get_bul().getGlobalBounds().width / 2.0,
			obj.get_bul().getPosition().y + obj.get_bul().getGlobalBounds().height / 2.0))) {
			enemies[i]->mob.setPosition(Vector2f(-enemies[i]->mob.getPosition().x, -enemies[i]->mob.getPosition().y));
			if (player.get_player().getGlobalBounds().contains(Vector2f(obj.get_bul().getPosition().x, obj.get_bul().getPosition().y))) {
				rules.decrease_lives();
				player.get_player().setColor(Color::Red);
				player.play_hit();
			}
			obj.refresh_bul();
		}
	}
}

void MapWithMobs::ChechCollisionWithObstacles(Player& player) {	; }

void MapWithStaticMotion::GenerateComplications()
{
	double x, y, size;
	bool fixation;

	srand(time(NULL));

	count_of_obstacles = rand() % (7 - 5 + 1) + 5;

	size = 75;

	obstacles = new Barriers * [count_of_obstacles];
	for (int i = 0; i < count_of_obstacles; i++)
	{
		obstacles[i] = new Barriers;

		do
		{
			x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
			y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

			int j = 0;
			fixation = true;
			while ((j < i) && (fixation))
			{
				if ((obstacles[j]->x1 > (x - size - 40)) && (obstacles[j]->x1 < (x + size + 40)) && (obstacles[j]->y1 > (y - size - 40)) && (obstacles[j]->y1 < (y + size + 40))) fixation = false;
				else j++;
			}

		} while (!fixation);

		obstacles[i]->barrier.setPosition(x, y);
		obstacles[i]->barrier.setSize(Vector2f(size, size));
		obstacles[i]->barrier.setTexture(&obstacles_texture);

		obstacles[i]->x1 = x;
		obstacles[i]->x2 = x + size;
		obstacles[i]->y1 = y;
		obstacles[i]->y2 = y + size;
	}
}

void MapWithStaticMotion::GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated)
{
	double x, y, size_1, size_2;
	bool fixation;

	size_1 = 50;
	size_2 = 75;

	for (int i = first_no_generated; i < first_no_generated + count_of_bonuses; i++)
	{
		do
		{
			x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size_1 - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
			y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size_1 - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

			int j = first_no_generated;
			fixation = true;
			while ((j < i) && (fixation))
			{
				if ((bonuses.GetCoordinateX(j) > (x - size_1 - 5)) && (bonuses.GetCoordinateX(j) < (x + size_1 + 5)) && (bonuses.GetCoordinateY(j) > (y - size_1 - 5)) && (bonuses.GetCoordinateY(j) < (y + size_1 + 5))) fixation = false;
				else j++;
			}

			if (fixation)
			{
				int k = 0;
				fixation = true;
				while ((k < count_of_obstacles) && (fixation))
				{
					if ((x > (obstacles[k]->x1 - size_1 - 5)) && (x < (obstacles[k]->x1 + size_2 + 5)) && (y > (obstacles[k]->y1 - size_1 - 5)) && (y < (obstacles[k]->y1 + size_2 + 5))) fixation = false;
					else k++;
				}
			}

		} while (!fixation);

		bonuses.SetSpriteCoordinates(i, x, y);
	}

	first_no_generated += count_of_bonuses;
}

void MapWithStaticMotion::GenerateCoordinatesOfPlayer(Player* player)
{
	double x, y, size_1, size_2, size_3;
	bool fixation;

	size_1 = 75;
	size_2 = 120;
	size_3 = 75;

	do
	{
		x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size_1 - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
		y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size_2 - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

		int i = 0;
		fixation = true;
		while ((i < count_of_obstacles) && (fixation))
		{
			if ((obstacles[i]->x1 >(x - size_3 - 5)) && (obstacles[i]->x1 < (x + size_1 + 5)) && (obstacles[i]->y1 > (y - size_3 - 5)) && (obstacles[i]->y1 < (y + size_2 + 5))) fixation = false;
			else i++;
		}
	} while (!fixation);

	player->set_position(x, y);
}

void MapWithStaticMotion::RedefinePlayer(Player*& player, Vector2f steps)
{
	Player* new_player = new Player_static(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), steps);
	delete player;
	player = new_player;
}

void MapWithStaticMotion::Draw(unique_ptr<RenderWindow>& window)
{
	window->draw(playground);
	for (int i = 0; i < count_of_obstacles; i++) window->draw(obstacles[i]->barrier);
}

void MapWithStaticMotion::CheckCollsisionWithMobs(Gun& obj) { ; }

void MapWithStaticMotion::ChechCollisionWithWalls(Player& player, Game& rules) { ; }

void MapWithStaticMotion::ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) { ; }

void MapWithStaticMotion::ChechCollisionWithObstacles(Player& player)
{
	for (int i = 0; i < count_of_obstacles; ++i)
	{
		if (obstacles[i]->barrier.getGlobalBounds().contains(player.get_player().getPosition().x + 40, player.get_player().getPosition().y + 90))
		{
			player.get_player().move(-player.get_steps().x, -player.get_steps().y);
			return;
		}
	}
}

void MapWithVectorMotion::GenerateComplications() { ; }

void MapWithVectorMotion::GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated)
{
	double x, y, size;
	bool fixation;

	size = 50;

	for (int i = first_no_generated; i < first_no_generated + count_of_bonuses; i++)
	{
		do
		{
			x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
			y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

			int j = first_no_generated;
			fixation = true;
			while ((j < i) && (fixation))
			{
				if ((bonuses.GetCoordinateX(j) > (x - size - 5)) && (bonuses.GetCoordinateX(j) < (x + size + 5)) && (bonuses.GetCoordinateY(j) > (y - size - 5)) && (bonuses.GetCoordinateY(j) < (y + size + 5))) fixation = false;
				else j++;
			}

		} while (!fixation);

		bonuses.SetSpriteCoordinates(i, x, y);
	}

	first_no_generated += count_of_bonuses;
}

void MapWithVectorMotion::GenerateCoordinatesOfPlayer(Player* player)
{
	double x, y, size_x, size_y;

	size_x = 75;
	size_y = 120;

	x = (double)rand() / (double)RAND_MAX * ((borders.x2 - size_x - 5) - (borders.x1 + 5)) + (borders.x1 + 5);
	y = (double)rand() / (double)RAND_MAX * ((borders.y2 - size_y - 5) - (borders.y1 + 5)) + (borders.y1 + 5);

	player->set_position(x, y);
}

void MapWithVectorMotion::RedefinePlayer(Player*& player, Vector2f steps)
{
	Player* new_player = new Player_vector(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), steps);
	delete player;
	player = new_player;
}

void MapWithVectorMotion::Draw(unique_ptr<RenderWindow>& window)
{
	window->draw(playground);
}

void MapWithVectorMotion::CheckCollsisionWithMobs(Gun& obj) { ; }

void MapWithVectorMotion::ChechCollisionWithWalls(Player& player, Game& rules)
{
	if (playground.getGlobalBounds().contains(player.get_player().getGlobalBounds().getPosition()))
	{
		if (player.get_player().getGlobalBounds().top == player.get_bords().getGlobalBounds().top) { rules.kill(); player.play_hit(); }
		if (player.get_player().getGlobalBounds().left == player.get_bords().getGlobalBounds().left) { rules.kill(); player.play_hit(); }
		if (player.get_player().getGlobalBounds().top + player.get_player().getGlobalBounds().height == player.get_bords().getGlobalBounds().top + player.get_bords().getGlobalBounds().height) { rules.kill(); player.play_hit(); }
		if (player.get_player().getGlobalBounds().left + player.get_player().getGlobalBounds().width == player.get_bords().getGlobalBounds().left + player.get_bords().getGlobalBounds().width) { rules.kill(); player.play_hit(); }
	}
}

void MapWithVectorMotion::ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) { ; }

void MapWithVectorMotion::ChechCollisionWithObstacles(Player& player) { ; }