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

bool Map::СheckPersonLocationOnMap(double current_x, double current_y)
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

void InvisibleMap::GenerateBonus() // генерация бонусов
{
	;
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

void InvisibleMap::CheckCollsisionWithMobs(Gun& obj)
{

}

void InvisibleMap::ChechCollisionWithWalls(Player& player, Game& rules)
{

}

void InvisibleMap::ChechCollisionWithPlayer(Player& player, Game& rules)
{
}

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

		fixation = true;
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

void MapWithMobs::GenerateBonus() // генерация бонусов
{
	;
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

void MapWithMobs::ChechCollisionWithWalls(Player& player, Game& rules)
{
}

void MapWithMobs::ChechCollisionWithPlayer(Player& player, Game& rules)
{
	for (int i = 0; i < count_of_enemies; i++) {
		if (player.get_player().getGlobalBounds().intersects(enemies[i]->mob.getGlobalBounds())) {
			enemies[i]->mob.setPosition(Vector2f(-enemies[i]->mob.getPosition().x, -enemies[i]->mob.getPosition().y));
			rules.decrease_lives();
		}
		if (enemies[i]->mob.getGlobalBounds().intersects(player.get_player().getGlobalBounds())) {
			enemies[i]->mob.setPosition(Vector2f(-enemies[i]->mob.getPosition().x, -enemies[i]->mob.getPosition().y));
			rules.decrease_lives();
		}
	}
}

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

		fixation = true;
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

void MapWithStaticMotion::GenerateBonus() // генерация бонусов
{
	;
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

void MapWithStaticMotion::CheckCollsisionWithMobs(Gun& obj)
{
}

void MapWithStaticMotion::ChechCollisionWithWalls(Player& player, Game& rules)
{
}

void MapWithStaticMotion::ChechCollisionWithPlayer(Player& player, Game& rules)
{
}

void MapWithVectorMotion::GenerateComplications() { ; }

void MapWithVectorMotion::GenerateBonus() // генерация бонусов
{
	;
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

void MapWithVectorMotion::CheckCollsisionWithMobs(Gun& obj)
{
}

void MapWithVectorMotion::ChechCollisionWithWalls(Player& player, Game& rules)
{
	if (playground.getGlobalBounds().contains(player.get_player().getGlobalBounds().getPosition()))
	{
		if (player.get_player().getGlobalBounds().top == player.get_bords().getGlobalBounds().top) rules.kill();
		if (player.get_player().getGlobalBounds().left == player.get_bords().getGlobalBounds().left) rules.kill();
		if (player.get_player().getGlobalBounds().top + player.get_player().getGlobalBounds().height == player.get_bords().getGlobalBounds().top + player.get_bords().getGlobalBounds().height) rules.kill();
		if (player.get_player().getGlobalBounds().left + player.get_player().getGlobalBounds().width == player.get_bords().getGlobalBounds().left + player.get_bords().getGlobalBounds().width) rules.kill();
	}
}

void MapWithVectorMotion::ChechCollisionWithPlayer(Player& player, Game& rules)
{
}
