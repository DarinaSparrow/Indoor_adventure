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
	Map* current_map;

public:

	Maps()
	{
		maps.push_back(new InvisibleMap);
		maps.push_back(new MapWithMobs);
		maps.push_back(new MapWithStaticMotion);
		maps.push_back(new MapWithVectorMotion);

		GenerateСoordinatesOfMaps();
		GenerateComplicationsOfMaps();
		// генерация бонусов на картах

		current_map = maps[0]; // изменить
	}

	string GetNameOfCurrentMap();

	void GenerateСoordinatesOfMaps();
	void GenerateComplicationsOfMaps();
	// генерация бонусов на картах

	// проверка на переход между картами

	void Draw(unique_ptr<RenderWindow>& window);

	~Maps()
	{
		vector <Map*> :: iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++)  delete* iter;
	}
};

