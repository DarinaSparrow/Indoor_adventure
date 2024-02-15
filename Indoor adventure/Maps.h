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

		Generate�oordinatesOfMaps();
		GenerateComplicationsOfMaps();
		// ��������� ������� �� ������

		current_map = maps[0]; // ��������
	}

	string GetNameOfCurrentMap();

	void Generate�oordinatesOfMaps();
	void GenerateComplicationsOfMaps();
	// ��������� ������� �� ������

	// �������� �� ������� ����� �������

	void Draw(unique_ptr<RenderWindow>& window);

	~Maps()
	{
		vector <Map*> :: iterator iter;

		for (iter = maps.begin(); iter != maps.end(); iter++)  delete* iter;
	}
};

