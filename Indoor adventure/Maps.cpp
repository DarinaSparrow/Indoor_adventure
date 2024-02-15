#include "Maps.h"

string Maps :: GetNameOfCurrentMap()
{
	return current_map->GetNameOfTheMap();
}

void Maps :: GenerateÑoordinatesOfMaps()
{
	srand(time(NULL));

	random_shuffle(maps.begin(), maps.end());

	maps[0]->SetCoordinates((win_width - win_height) / 2, 0, win_width / 2, win_height / 2);
	maps[1]->SetCoordinates(win_width / 2, 0, (win_width + win_height) / 2, win_height / 2);
	maps[2]->SetCoordinates((win_width - win_height) / 2, win_height / 2, win_width / 2, win_height);
	maps[3]->SetCoordinates(win_width / 2, win_height / 2, (win_width + win_height) / 2, win_height);
}

void Maps :: GenerateLimitsOfMaps()
{
	maps[0]->SetLimits(true);
	maps[1]->SetLimits(false);
	maps[2]->SetLimits(false);
	maps[3]->SetLimits(true);
}

void Maps :: GenerateComplicationsOfMaps()
{
	vector <Map*> ::iterator iter;

	for (iter = maps.begin(); iter != maps.end(); iter++) (*iter)->GenerateComplications();
}

void Maps :: InstallTheInitialMap(Player* player) // ïåðåäåëàòü ïîñëå ãåíåðàöèè ïåðñîíàæà
{
	if (player->get_player().getPosition().x + 37 < win_width / 2)
	{
		if (player->get_player().getPosition().y + 60 < win_height / 2) current_map = maps[0];
		else current_map = maps[2];
	}
	else
	{
		if (player->get_player().getPosition().y + 60 < win_height / 2) current_map = maps[1];
		else current_map = maps[3];
	}
}

void Maps::CheckTheTransitionBetweenMaps(Player*& player)
{
	if (!current_map->ÑheckPersonLocationOnMap(player->get_player().getPosition().x + 40, player->get_player().getPosition().y + 90))
	{
		for (int i = 0; i < maps.size(); i++)
		{
			if (current_map != maps[i])
			{
				if (maps[i]->ÑheckPersonLocationOnMap(player->get_player().getPosition().x + 40, player->get_player().getPosition().y + 90))
				{
					if (current_map->GetNameOfTheMap() == "Vector motion map") {
						current_map = maps[i];
						current_map->RedefinePlayer(player, Vector2f(0,0));
					}
					else {
						current_map = maps[i];
						current_map->RedefinePlayer(player, player->get_steps());
					}
				}
			}
		}
	}
	else {
		if (current_map->GetNameOfTheMap() == "Vector motion map") {
			Player_vector* tmp = new Player_vector(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), player->get_steps());
			if (player->get_params() != tmp->get_params()) 	current_map->RedefinePlayer(player, player->get_steps());
		}
		else if (current_map->GetNameOfTheMap() == "Invisible map") {
			Player_invisible* tmp = new Player_invisible(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), player->get_steps());
			if (player->get_params() != tmp->get_params()) 	current_map->RedefinePlayer(player, player->get_steps());
		}
		else if (current_map->GetNameOfTheMap() == "Map with hostile mobs") {
			Player_danger_zone* tmp = new Player_danger_zone(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), player->get_steps());
			if (player->get_params() != tmp->get_params()) 	current_map->RedefinePlayer(player, player->get_steps());
		}
		else if (current_map->GetNameOfTheMap() == "Static motion map") {
			Player_static* tmp = new Player_static(player->get_bords(), player->get_player().getPosition(), player->get_sound(), player->get_cur_anim(), player->get_steps());
			if (player->get_params() != tmp->get_params()) 	current_map->RedefinePlayer(player, player->get_steps());
		}
	}
}

void Maps :: Draw(unique_ptr<RenderWindow>& window)
{
	vector <Map*> :: iterator iter;

	for (iter = maps.begin(); iter != maps.end(); iter++) (*iter)->Draw(window);
}