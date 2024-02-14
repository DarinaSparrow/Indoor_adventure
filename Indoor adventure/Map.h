#pragma once

#include "header.h"
#include <ctime>

class HostileMobs
{
private:

protected:

};

class Map
{
protected:

	RectangleShape playground;
	Texture playground_texture;
	struct Coordinates { double x1, x2, y1, y2; };
	Coordinates borders;

public:

	Map() { ; }

	void SetCoordinates(double x1, double y1, double x2, double y2)
	{
		playground.setPosition(x1, y1);
		playground.setSize(Vector2f(x2 - x1, y2 - y1));

		borders.x1 = x1;
		borders.x2 = x2;
		borders.y1 = y1;
		borders.y2 = y2;
	}

	virtual void GenerateComplications() = 0; // генерация усложнений на конкретной карте

	virtual void GenerateBonus() = 0; // генерация бонусов на конкретной карте

	virtual void Draw(RenderWindow& window) = 0;

	RectangleShape& get_map()
	{
		return playground;
	}

	~Map() { ; }
};

class InvisibleMap : public Map
{
public:

	InvisibleMap()
	{
		playground_texture.loadFromFile("Resourses/Playground 1.png");
		playground.setTexture(&playground_texture);
	}

	void GenerateComplications() { ; }

	void GenerateBonus() // генерация бонусов на карте
	{
		;
	}

	void Draw(RenderWindow& window)
	{
		window.draw(playground);
	}

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
		playground_texture.loadFromFile("Resourses/Playground 2.png");
		playground.setTexture(&playground_texture);
	}

	void GenerateComplications()
	{
		srand(time(NULL));

		count_of_enemies = rand() % (5 - 3 + 1) + 3;

		enemies = new HostileMobs * [count_of_enemies];
		for (int i = 0; i < count_of_enemies; i++) enemies[i] = new HostileMobs;

		// генерация начального расположения
	}

	void GenerateBonus() // генерация бонусов на карте
	{
		;
	}

	void Draw(RenderWindow& window)
	{
		window.draw(playground);
		// отрисовка мобов
	}

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
		playground_texture.loadFromFile("Resourses/Playground 3.png");
		playground.setTexture(&playground_texture);

		obstacles_texture.loadFromFile("Resourses/Box.png");
	}

	void GenerateComplications()
	{
		double x, y;
		bool fixation;

		srand(time(NULL));

		count_of_obstacles = rand() % (7 - 5 + 1) + 5;

		obstacles = new Barriers * [count_of_obstacles];
		for (int i = 0; i < count_of_obstacles; i++)
		{
			obstacles[i] = new Barriers;

			fixation = true;
			do
			{
				x = (double)rand() / (double)RAND_MAX * ((borders.x2 - 150) - borders.x1) + borders.x1;
				y = (double)rand() / (double)RAND_MAX * ((borders.y2 - 150) - borders.y1) + borders.y1;

				for (int j = 0; j < i; j++)
				{
					;
					// проверка на фиксацию
				}

			} while (!fixation);

			obstacles[i]->barrier.setPosition(x, y);
			obstacles[i]->barrier.setSize(Vector2f(150, 150));
			obstacles[i]->barrier.setTexture(&obstacles_texture);

			obstacles[i]->x1 = x;
			obstacles[i]->x2 = x + 150;
			obstacles[i]->y1 = y;
			obstacles[i]->y2 = y + 150;
		}
	}

	void GenerateBonus() // генерация бонусов на карте
	{
		;
	}

	void Draw(RenderWindow& window)
	{
		window.draw(playground);
		for (int i = 0; i < count_of_obstacles; i++) window.draw(obstacles[i]->barrier);
	}

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
		playground_texture.loadFromFile("Resourses/Playground 4.png");
		playground.setTexture(&playground_texture);
	}

	void GenerateComplications() // генерация усложнений на карте
	{
		;
	}

	void GenerateBonus() // генерация бонусов на карте
	{
		;
	}

	void Draw(RenderWindow& window)
	{
		window.draw(playground);
	}

	~MapWithVectorMotion() { ; }
};