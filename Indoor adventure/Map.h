#pragma once

#include "header.h"
#include "Player.h"
#include "Bonus.h"
#include "Gun.h"
#include "Game.h"
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
	virtual void GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated) = 0;

	bool ÑheckPersonLocationOnMap(double current_x, double current_y);
	virtual void RedefinePlayer(Player*& player, Vector2f steps) = 0;

	virtual void CheckCollsisionWithMobs(Gun& obj) = 0;
	virtual void ChechCollisionWithWalls(Player& player, Game& rules) = 0;
	virtual void ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) = 0;

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
	void GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated) override;

	void RedefinePlayer(Player*& player, Vector2f steps) override;

	void Draw(unique_ptr<RenderWindow>& window) override;

	void CheckCollsisionWithMobs(Gun& obj) override;
	void ChechCollisionWithWalls(Player& player, Game& rules) override;
	void ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) override;

	~InvisibleMap() { ; }
};

class MapWithMobs : public Map
{
private:

	int count_of_enemies;
	struct Mob
	{
		RectangleShape mob;
		double x1, x2, y1, y2;
	};
	Texture enemies_texture;
	Mob** enemies;

public:

	MapWithMobs()
	{
		name = "Mobs";

		playground_texture.loadFromFile("Resourses/Playground 2.png");
		playground.setTexture(&playground_texture);

		enemies_texture.loadFromFile("Resourses/Mob.png");
	}

	void GenerateComplications() override;
	void GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated) override;

	void RedefinePlayer(Player*& player, Vector2f steps) override;

	void Draw(unique_ptr<RenderWindow>& window) override;

	void CheckCollsisionWithMobs(Gun& obj) override;
	void ChechCollisionWithWalls(Player& player, Game& rules) override;
	void ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) override;

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
		name = "Static";

		playground_texture.loadFromFile("Resourses/Playground 3.png");
		playground.setTexture(&playground_texture);

		obstacles_texture.loadFromFile("Resourses/Box.png");
	}

	void GenerateComplications() override;
	void GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated) override;

	void RedefinePlayer(Player*& player, Vector2f steps) override;

	void Draw(unique_ptr<RenderWindow>& window) override;

	void CheckCollsisionWithMobs(Gun& obj) override;
	void ChechCollisionWithWalls(Player& player, Game& rules) override;
	void ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) override;

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
		name = "Vector";

		playground_texture.loadFromFile("Resourses/Playground 4.png");
		playground.setTexture(&playground_texture);
	}

	void GenerateComplications() override;
	void GenerateBonus(Bonus& bonuses, int count_of_bonuses, int& first_no_generated) override;

	void RedefinePlayer(Player*& player, Vector2f steps) override;

	void Draw(unique_ptr<RenderWindow>& window) override;

	void CheckCollsisionWithMobs(Gun& obj) override;
	void ChechCollisionWithWalls(Player& player, Game& rules) override;
	void ChechCollisionWithPlayer(Gun& obj, Player& player, Game& rules) override;

	~MapWithVectorMotion() { ; }
};