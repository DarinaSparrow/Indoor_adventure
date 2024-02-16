#pragma once

#include "Animator.h"

struct Coins
{
	Sprite sprite_coin;
	bool caught;
};

class Bonus
{
private:

	int total;
	int collected;

	Texture bonus_texture;

	Coins* coins;

public:
	Bonus()
	{
		total = 75;
		collected = 0;

		bonus_texture.loadFromFile("Resourses/111.png");

		coins = new Coins[total];
		for (int i = 0; i < total; i++)
		{
			coins[i].sprite_coin.setTexture(bonus_texture);
			coins[i].sprite_coin.setScale(0.02, 0.02);
			coins[i].caught = false;
		}
	}

	int GetTotal();
	double GetCoordinateX(int i);
	double GetCoordinateY(int i);

	Coins* get_coins();

	void SetSpriteCoordinates(int i, double x, double y);

	void Draw(unique_ptr<RenderWindow>& window);

	~Bonus()
	{
		delete[] coins;
	}
};