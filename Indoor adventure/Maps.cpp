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

void Maps :: GenerateComplicationsOfMaps()
{
	vector <Map*> ::iterator iter;

	for (iter = maps.begin(); iter != maps.end(); iter++) (*iter)->GenerateComplications();
}

void Maps :: Draw(unique_ptr<RenderWindow>& window)
{
	vector <Map*> ::iterator iter;

	for (iter = maps.begin(); iter != maps.end(); iter++)
	{
		auto draw_map = (*iter)->Draw();
		window->draw(draw_map);
	}
}