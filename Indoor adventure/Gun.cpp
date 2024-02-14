#include "Gun.h"

void Gun::update(Time const& delta_time)
{
    aim.setPosition(Vector2f(pos_x - width_bul, pos_y - height_bul));
}

Sprite& Gun::get_aim()
{
    return aim;
}

Sprite& Gun::get_bullet()
{
    return bullet;
}

void Gun::set_x(int x)
{
    pos_x = x;
}

void Gun::set_y(int y)
{
    pos_y = y;
}
