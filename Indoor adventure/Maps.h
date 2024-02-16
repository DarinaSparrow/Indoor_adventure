#pragma once

#include "header.h"
#include "Map.h"
#include "Player.h"
#include "Bonus.h"
#include "Gun.h"
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

		Generate—oordinatesOfMaps();
		GenerateLimitsOfMaps();
		GenerateComplicationsOfMaps();
	}

	string GetNameOfCurrentMap();

	void Generate—oordinatesOfMaps();
	void GenerateLimitsOfMaps();
	void GenerateComplicationsOfMaps();
	void GenerateBonuses(Bonus& bonuses);
	void GenerateCoordinatesOfPlayer(Player*& player);

	//void InstallTheInitialMap(Player*& player);

	void CheckTheTransitionBetweenMaps(Player*& player, Gun& gun);

	void ChechCollisionWithMobs(Gun& obj);
	void ChechCollisionWithWalls(Player& player, Game& rules);
	void ChechCollisionWithPlayer(Gun& obj,Player& player, Game& rules);
	void ChechCollisionWithObstacles(Player& player);

	void Draw(unique_ptr<RenderWindow>& window);

	void Restart(Bonus& bonuses, Player*& player);

	~Maps()
	{
		vector <Map*> :: iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++)  delete* iter;
	}
};