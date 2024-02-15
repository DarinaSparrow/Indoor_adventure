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