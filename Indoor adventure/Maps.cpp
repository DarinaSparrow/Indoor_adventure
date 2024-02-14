#include "Maps.h"


Map::Map(double x, double y, double width, double height, RenderWindow& window) : my_window(window)
{
	borders.x = x;
	borders.y = y;
	borders.max_x = x + width;
	borders.max_y = y + height;

	playground.setSize(Vector2f(width, height));
	playground.setPosition(Vector2f(x, y));
}


void Map::set_map(double x, double y, double width, double height)
{

}


RectangleShape& Map::get_map()
{
	return playground;
}


void Maps::generate_maps()
{

}
