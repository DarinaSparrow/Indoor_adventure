#pragma once
#include "Engine.h"


// ����� ����� ����� �� ������� ���
// ���������� ����������
class Map
{
private:
	RectangleShape playground;

	RenderWindow& my_window;

	// ������� ������� ����
	// �������� �� ����� ������������ ��� ����� ����� ���������� � ���������
	struct Borders
	{
		double x;
		double y;
		double max_x;
		double max_y;
	};

	Borders borders{ 0 };

	bool type_of_move;
	bool visible;

public:
	Map(double x, double y, double width, double height, RenderWindow& window);

	void set_map(double x, double y, double width, double height);
	RectangleShape& get_map();

	virtual void draw() = 0;
	virtual void generate_bonus() = 0;
};


// ����� ���� ������� �������
// ������ ���� ��������������� ������, �������� ���� ������ ��� �� �����
// ��� ���� ����� ���� ����
class Maps
{
private:
	vector<Map> maps;

public:
	void generate_maps();

};

