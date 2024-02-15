#pragma once

#include "header.h"
#include "HostileMobs.h"
#include <ctime>

class Map
{
protected:

	string name;
	RectangleShape playground;
	Texture playground_texture;
	struct Coordinates { double x1, x2, y1, y2; };
	Coordinates borders;

public:

	Map() { ; }

	void SetCoordinates(double x1, double y1, double x2, double y2);

	string GetNameOfTheMap();

	virtual void GenerateComplications() = 0; // генерация усложнений на конкретной карте
	virtual void GenerateBonus() = 0; // генерация бонусов на конкретной карте

	virtual RectangleShape& Draw() = 0; // отрисовка

	~Map() { ; }
};

class InvisibleMap : public Map
{
public:

	InvisibleMap()
	{
		name = "Invisible";

		playground_texture.loadFromFile("Resourses/Playground 1.png");
		playground.setTexture(&playground_texture);
	}

	void GenerateComplications() override;
	void GenerateBonus() override; // генерация бонусов

	RectangleShape& Draw() override;

	~InvisibleMap() { ; }
};

class MapWithMobs : public Map
{
private:

	int count_of_enemies;
	HostileMobs** enemies;

public:

	MapWithMobs()
	{
		name = "Mobs";

		playground_texture.loadFromFile("Resourses/Playground 2.png");
		playground.setTexture(&playground_texture);
	}

	void GenerateComplications() override; // генерация мобов
	void GenerateBonus() override; // генерация бонусов

	RectangleShape& Draw() override; // отрисовка

	~MapWithMobs()
	{
		for (int i = 0; i < count_of_enemies; i++) delete enemies[i];
		delete[] enemies;
	}
};

class MapWithStaticMotion : public Map
{
private:

	int count_of_obstacles;
	struct Barriers
	{
		RectangleShape barrier;
		double x1, x2, y1, y2;
	};
	Texture obstacles_texture;
	Barriers** obstacles;

public:

	MapWithStaticMotion()
	{
		name = "Static movement";

		playground_texture.loadFromFile("Resourses/Playground 3.png");
		playground.setTexture(&playground_texture);

		obstacles_texture.loadFromFile("Resourses/Box.png");
	}

	void GenerateComplications() override; // генерация препятствий
	void GenerateBonus() override; // генерация бонусов

	RectangleShape& Draw() override; // отрисовка

	~MapWithStaticMotion()
	{
		for (int i = 0; i < count_of_obstacles; i++) delete obstacles[i];
		delete[] obstacles;
	}
};

class MapWithVectorMotion : public Map
{
public:

	MapWithVectorMotion()
	{
		name = "Vector movement";

		playground_texture.loadFromFile("Resourses/Playground 4.png");
		playground.setTexture(&playground_texture);
	}

	void GenerateComplications() override; // генерация препятствий
	void GenerateBonus() override; // генерация бонусов

	RectangleShape& Draw() override; // отрисовка

	~MapWithVectorMotion() { ; }
};