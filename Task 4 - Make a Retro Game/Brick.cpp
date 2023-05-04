#include "Brick.h"
#include "raylib.h"

Brick::Brick()
{
	brickSize = { (float)GetScreenWidth() / 20, 40 };
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			position = { j * brickSize.x + brickSize.x / 2, i * brickSize.y + 50 };
			active = true;
		}
	}
}

float Brick::GetPositionX()
{
	return position.x;
}

float Brick::GetPositionY()
{
	return position.y;
}

bool Brick::IsAlive()
{
	return active;
}

void Brick::Kill()
{
	active = false;
}