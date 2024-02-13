#include "Bonus.h"


Bonus::Bonus(RenderWindow& window, Vector2f my_pos, double time, Vector2i sprite_size)
{

}


void Bonus::set_catch_it(bool status)
{
	catch_it = status;
}


bool Bonus::get_catch_it() const
{
	return catch_it;
}


Sprite& Bonus::get_coin()
{
	return sprite_coin;
}
