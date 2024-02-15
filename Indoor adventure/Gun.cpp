#include "Gun.h"


void Gun::shoot()
{
    shooting = true;

	dX_step = pos_x - bullet.getPosition().x;
	dY_step = pos_y - bullet.getPosition().y;

	step = Vector2f(dX_step * 0.05, dY_step * 0.05);
}


bool Gun::check_shoot()
{
	return shooting;
}


void Gun::update(Time const& delta_time)
{
    Vector2f last_pos = aim.getPosition();

    aim.setPosition(Vector2f(pos_x - width_aim, pos_y - height_aim));
    if (!border_zone.getGlobalBounds().contains(Vector2f(aim.getPosition().x + aim.getGlobalBounds().width / 2.0, aim.getPosition().y + aim.getGlobalBounds().height / 2.0))){
		aim.setPosition(last_pos);
    }

	if ((pos_x - bullet.getPosition().x) * (pos_x - bullet.getPosition().x)
		+ (pos_y - bullet.getPosition().y) * (pos_y - bullet.getPosition().y) < 7500) {
		aim.setPosition(last_pos);
	}

	if (shooting) {
		update_time += delta_time;

		if (update_time > microseconds(3))
		{
			update_time = microseconds(0);

			bullet.move(step);

			if (!border_zone.getGlobalBounds().contains(Vector2f(bullet.getPosition().x + bullet.getGlobalBounds().width / 2.0, bullet.getPosition().y + bullet.getGlobalBounds().height / 2.0))) {
				shooting = false;
			}
		}
	}
	else {
		dX = pos_x - bullet.getPosition().x;
		dY = pos_y - bullet.getPosition().y;
		rotation = (atan2(dY, dX)) * 180 / 3.14159265;
		bullet.setRotation(90 + rotation);

	}
}


void Gun::update_bullet_pos(Sprite player)
{
    if (!shooting) {
        bullet.setPosition(Vector2f(player.getGlobalBounds().left + player.getGlobalBounds().width / 2, 
            player.getGlobalBounds().top + player.getGlobalBounds().height / 2));
    }
}


void Gun::update_mouse_pos(Vector2i pos)
{
    pos_x = pos.x;
    pos_y = pos.y;
}


Sprite& Gun::get_bul()
{
	return bullet;
}

void Gun::refresh_bul()
{
	shooting = false;
}


void Gun::draw(RenderWindow& window) const
{
    if (!shooting) {
        window.draw(aim);
    }
    else {
        window.draw(bullet);
    }
}
