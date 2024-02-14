#pragma once
#include "header.h"
#include "Animator.h"
#include "chrono"
#include <vector>


// ����� ��� ���������� �����������
// �� ���������� ��� ������ � ������ ��������, � ����� ��������� ��������������
// ������ ����� ������ �������� ��������� ����� ��� ������� ����
// �������� ���� ���������� ��-����� 
class Game : public Drawable, public Transformable
{
private:
	RectangleShape maps;

	Sprite background_sprite;
	Sprite lives_sprite;

	Font game_font;
	Text timer_text;
	ostringstream timer_string;

	float timer;
	int lives;

public:
	Game();
	RectangleShape& get_maps();

	void decrease_lives();

	void update(Time const& delta_time);

	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		target.draw(background_sprite);
		target.draw(timer_text);
		target.draw(lives_sprite);
		target.draw(maps);
	}
};