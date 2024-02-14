#pragma once

#include "header.h"
#include "Map.h"
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>

class Maps
{
private:

	vector <Map*> maps;

public:

	Maps()
	{
		maps.push_back(new InvisibleMap);
		maps.push_back(new MapWithMobs);
		maps.push_back(new MapWithStaticMotion);
		maps.push_back(new MapWithVectorMotion);

		GenerateÑoordinatesOfMaps();
		GenerateComplicationsOfMaps();
		// ãåíåðàöèÿ áîíóñîâ íà êàðòå
	}

	void GenerateÑoordinatesOfMaps()
	{
		srand(time(NULL));

		random_shuffle(maps.begin(), maps.end());

		maps[0]->SetCoordinates((win_width - win_height) / 2, 0, win_width / 2, win_height / 2);
		maps[1]->SetCoordinates(win_width / 2, 0, (win_width + win_height) / 2, win_height / 2);
		maps[2]->SetCoordinates((win_width - win_height) / 2, win_height / 2, win_width / 2, win_height);
		maps[3]->SetCoordinates(win_width / 2, win_height / 2, (win_width + win_height) / 2, win_height);
	}

	void GenerateComplicationsOfMaps()
	{
		vector <Map*> ::iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++) (*iter)->GenerateComplications();
	}

	/*void Draw(RenderWindow& window)
	{
		vector <Map*> ::iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++) (*iter)->Draw(window);
	}*/

	void Draw(unique_ptr<RenderWindow>& window)
	{
		vector <Map*> ::iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++)
		{
			auto draw_map = (*iter)->get_map();
			window->draw(draw_map);
		}
	}

	~Maps()
	{
		vector <Map*> ::iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++)  delete* iter;
	}
};

