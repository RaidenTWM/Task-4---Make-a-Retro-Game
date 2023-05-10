#include "Brick.h"
#include "raylib.h"

Vector2 Brick::brickSize;
Brick::Brick(int i, int j)
{
	Brick::brickSize = { (float)(GetScreenWidth() / BRICKS_PER_LINE - 5), (float)GetScreenHeight() / 18};
	position = { 50 + j * brickSize.x + brickSize.x / 2, i * brickSize.y + 75 };
	active = true;
	brickSprite = LoadTexture("Images/Brick_Sprite.png");
	brickSprite.width = brickSize.x;
	brickSprite.height = brickSize.y;
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

void Brick::Unload()
{
	UnloadTexture(brickSprite);
}
