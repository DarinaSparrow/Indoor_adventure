#pragma once
#include "header.h"
#include "AssertManager.h"


class Gun
{
private:
	Sprite aim;
	Sprite bullet;
	double pos_x, pos_y;

	//void move(double step = 5.0);
public:
	Gun(RenderWindow& window, Sprite player)
	{
		pos_x = Mouse::getPosition().x;
		pos_y = Mouse::getPosition().y;

		Mouse::setPosition(Vector2i(pos_x, pos_y));

		aim.setTexture(AssertManager::get_texture("Resourses/crosshair.png"));
		bullet.setTexture(AssertManager::get_texture("Resourses/bullet.png"));

		aim.setTextureRect(IntRect(0, 0, aim.getGlobalBounds().width, aim.getGlobalBounds().height));
		bullet.setTextureRect(IntRect(0, 0, bullet.getGlobalBounds().width, bullet.getGlobalBounds().height));

		aim.setPosition(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
		bullet.setPosition(Vector2f(player.getGlobalBounds().left + player.getGlobalBounds().width / 6, player.getGlobalBounds().top + player.getGlobalBounds().height / 2));
	
		bullet.scale(Vector2f(0.5, 0.5));
	}


	//void shoot();
	void update(Time const& delta_time);

	Sprite& get_aim();
	Sprite& get_bullet();

	void set_x(int x);
	void set_y(int y);
};

