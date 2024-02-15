#pragma once
#include "header.h"
#include "AssertManager.h"


class Gun
{
private:
	Sprite aim;
	Sprite bullet;
	double pos_x, pos_y;
	double width_aim, height_aim;

	double dX, dY, dX_step, dY_step;
	bool shooting;
	double rotation;

	RectangleShape border_zone;
	Time update_time;

	Vector2f step;

public:
	Gun(RenderWindow& window, Sprite player, RectangleShape& border_zone) : border_zone(border_zone)
	{
		pos_x = Mouse::getPosition(window).x;
		pos_y = Mouse::getPosition(window).y;

		aim.setTexture(AssertManager::get_texture("Resourses/crosshair.png"));
		bullet.setTexture(AssertManager::get_texture("Resourses/bullet.png"));

		aim.setTextureRect(IntRect(0, 0, aim.getGlobalBounds().width, aim.getGlobalBounds().height));
		bullet.setTextureRect(IntRect(0, 0, bullet.getGlobalBounds().width, bullet.getGlobalBounds().height));

		width_aim = double(aim.getGlobalBounds().width) / 2.0;
		height_aim= double(aim.getGlobalBounds().height) / 2.0;

		aim.setPosition(Vector2f(pos_x - width_aim, pos_y - height_aim));
		bullet.setPosition(Vector2f(player.getGlobalBounds().left + player.getGlobalBounds().width / 6, player.getGlobalBounds().top + player.getGlobalBounds().height / 2));

		bullet.scale(Vector2f(0.5, 0.5));
		bullet.setOrigin(bullet.getGlobalBounds().width / 2, bullet.getGlobalBounds().height / 2);

		dX = pos_x - bullet.getPosition().x;
		dY = pos_y - bullet.getPosition().y;
		rotation = (atan2(dY, dX)) * 180 / 3.14159265;
		bullet.setRotation(90 + rotation);

		shooting = false;
		step = Vector2f(0, 0);
	}


	void shoot();
	bool check_shoot();

	void update(Time const& delta_time);
	void update_bullet_pos(Sprite player);
	void update_mouse_pos(Vector2i pos);

	void draw(RenderWindow& window) const;
};

