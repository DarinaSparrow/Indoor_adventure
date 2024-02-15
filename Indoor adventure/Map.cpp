#include "Map.h"

void Map :: SetCoordinates(double x1, double y1, double x2, double y2)
{
	playground.setPosition(x1, y1);
	playground.setSize(Vector2f(x2 - x1, y2 - y1));

	borders.x1 = x1;
	borders.x2 = x2;
	borders.y1 = y1;
	borders.y2 = y2;
}

string Map :: GetNameOfTheMap() { return name; }

void InvisibleMap :: GenerateComplications() { ; }

void InvisibleMap :: GenerateBonus() // ��������� �������
{
	;
}

RectangleShape& InvisibleMap :: Draw()
{
	return playground;
}

void MapWithMobs :: GenerateComplications() // ��������� �����
{
	srand(time(NULL));

	count_of_enemies = rand() % (5 - 3 + 1) + 3;

	enemies = new HostileMobs * [count_of_enemies];
	for (int i = 0; i < count_of_enemies; i++) enemies[i] = new HostileMobs;

	// ��������� ���������� ������������
}

void MapWithMobs :: GenerateBonus() // ��������� �������
{
	;
}

RectangleShape& MapWithMobs :: Draw() // ���������
{
	return playground;
	// ��������� �����
}

void MapWithStaticMotion :: GenerateComplications() // ��������� �����������
{
	double x, y;
	bool fixation;

	srand(time(NULL));

	count_of_obstacles = rand() % (7 - 5 + 1) + 5;

	obstacles = new Barriers * [count_of_obstacles];
	for (int i = 0; i < count_of_obstacles; i++)
	{
		obstacles[i] = new Barriers;

		fixation = true;
		do
		{
			x = (double)rand() / (double)RAND_MAX * ((borders.x2 - 150) - borders.x1) + borders.x1;
			y = (double)rand() / (double)RAND_MAX * ((borders.y2 - 150) - borders.y1) + borders.y1;

			for (int j = 0; j < i; j++)
			{
				;
				// �������� �� ��������
			}

		} while (!fixation);

		obstacles[i]->barrier.setPosition(x, y);
		obstacles[i]->barrier.setSize(Vector2f(150, 150));
		obstacles[i]->barrier.setTexture(&obstacles_texture);

		obstacles[i]->x1 = x;
		obstacles[i]->x2 = x + 150;
		obstacles[i]->y1 = y;
		obstacles[i]->y2 = y + 150;
	}
}

void MapWithStaticMotion :: GenerateBonus() // ��������� �������
{
	;
}

RectangleShape& MapWithStaticMotion :: Draw() // ���������
{
	return playground;
	// ��������� �����������
}

void MapWithVectorMotion :: GenerateComplications() // ��������� �����������
{ 
	;
}

void MapWithVectorMotion :: GenerateBonus() // ��������� �������
{
	;
}

RectangleShape& MapWithVectorMotion :: Draw() // ���������
{
	return playground;
	// ��������� �����������
}