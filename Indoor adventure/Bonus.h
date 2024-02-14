#pragma once
#include "Maps.h"


// ����� ������, �� ����� ��� ��������� ������� �� ����� � ������ Maps
// ���������� ����������� ���
class Bonus
{
private:
	// ������� ��������� �������
	// ��������������� ��� ��� ������ ����� ��� ����, �� �������� ��� �� �����
	struct Borders
	{
		double x;
		double y;
		double max_x;
		double max_y;
	};

	Borders borders_of_generate;
	Sprite sprite_coin;
	Animator anim_coin = Animator(sprite_coin);

	Time time_update;
	bool catch_it = false;
public:
	Bonus(RenderWindow& window, Vector2f my_pos = Vector2f(S_W / 2, 650), double time = 0.3,
		Vector2i sprite_size = Vector2i(192, 256));

	void set_catch_it(bool status);

	bool get_catch_it() const;

	Sprite& get_coin();
};

