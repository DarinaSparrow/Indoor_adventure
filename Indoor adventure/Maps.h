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

//Вынести из конструктора генерации и переопределение
//Точка для проверки нахождения на карте и размеры препятствий - вручную
//Менеджер ресурсов для текстур

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
		GenerateLimitsOfMaps();
		GenerateComplicationsOfMaps();
	}

	string GetNameOfCurrentMap();

	void GenerateСoordinatesOfMaps();
	void GenerateLimitsOfMaps();
	void GenerateComplicationsOfMaps();
	void GenerateBonuses(Bonus& bonuses);
	void GenerateCoordinatesOfPlayer(Player*& player);

	//void InstallTheInitialMap(Player*& player);

	void CheckTheTransitionBetweenMaps(Player*& player);

	void ChechCollisionWithMobs(Gun& obj);
	void ChechCollisionWithWalls(Player& player, Game& rules);
	void ChechCollisionWithPlayer(Gun& obj,Player& player, Game& rules);


	void ChechCollisionWithObstacles(Player& player);

	void Draw(unique_ptr<RenderWindow>& window);

	~Maps()
	{
		vector <Map*> :: iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++)  delete* iter;
	}
};