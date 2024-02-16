#include "Bonus.h"

int Bonus::GetTotal()
{
	return total;
}

double Bonus::GetCoordinateX(int i)
{
	return coins[i].sprite_coin.getPosition().x;
}
double Bonus::GetCoordinateY(int i)
{
	return coins[i].sprite_coin.getPosition().y;
}

Coins* Bonus::get_coins()
{
	return coins;
}

void Bonus::SetSpriteCoordinates(int i, double x, double y)
{
	coins[i].sprite_coin.setPosition(x, y);
}

void Bonus::Draw(unique_ptr<RenderWindow>& window)
{
	for (int i = 0; i < total; i++)
	{
		window->draw(coins[i].sprite_coin);
	}
}

void Bonus::Restart()
{
	collected = 0;

	for (int i = 0; i < total; i++)	{ coins[i].caught = false; }
}