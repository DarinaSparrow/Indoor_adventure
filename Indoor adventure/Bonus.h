#pragma once
#include "Maps.h"


// Класс бонуса, он нужен для генерации бонусов по карте в классе Maps
// Реализации практически нет
//class Bonus
//{
//private:
//	// Границы генерации бонусов
//	// Подразумевается что для каждой карты они свои, но возможно это не нужно
//	struct Coins
//	{
//		Sprite sprite_coin;
//		double x1, y1, x2, y2;
//		bool caught = false;
//	};
//	
//	Coins* coins;
//	Animator anim_coin = Animator(sprite_coin);
//	int total;
//	int collected;
//
//	
//public:
//	Bonus(RenderWindow& window, Vector2f my_pos = Vector2f(win_width / 2, 650), double time = 0.3,
//		Vector2i sprite_size = Vector2i(192, 256))
//	{
//		auto& idle_static = anim_coin.create_animation("static", "Resourses/down.png",
//			seconds(0.3), true);
//		idle_static.AddFrames(Vector2i(0, 0), Vector2i(50, 80), 1, 1);
//	}
//
//	void set_catch_it(bool status);
//
//	bool get_catch_it() const;
//
//	Sprite& get_coin();
//};

