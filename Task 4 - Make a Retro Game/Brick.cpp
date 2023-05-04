#include "Brick.h"
#include "raylib.h"

const Vector2 Brick::brickSize = { 1280 / BRICKS_PER_LINE, 40 };
Brick::Brick(int i, int j)
{
	position = { j * brickSize.x + brickSize.x / 2, i * brickSize.y + 75 };
	active = true;
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