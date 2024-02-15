#pragma once

#include "header.h"
#include "Player.h"
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
	bool limits;

public:

	Map() { ; }

	void SetCoordinates(double x1, double y1, double x2, double y2);
	void SetLimits(bool limits);

	string GetNameOfTheMap();

	virtual void GenerateComplications() = 0;
	virtual void GenerateBonus() = 0;

	bool СheckPersonLocationOnMap(double current_x, double current_y);
	virtual void RedefinePlayer(Player*& player) = 0;
		
	virtual void Draw(unique_ptr<RenderWindow>& window) = 0;

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

	void RedefinePlayer(Player*& player) override;

	void Draw(unique_ptr<RenderWindow>& window) override;

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

	void RedefinePlayer(Player*& player) override;

	void Draw(unique_ptr<RenderWindow>& window) override; // отрисовка

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

	void RedefinePlayer(Player*& player) override;

	void Draw(unique_ptr<RenderWindow>& window) override; // отрисовка

	~MapWithVectorMotion() { ; }
};