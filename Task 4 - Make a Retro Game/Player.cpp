#include "Player.h"
#include "raylib.h"
 
Player::Player()
{
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() * 7 / 8 };
	size = { (float)GetScreenWidth() / 10, 20 };
	life = 5;
}

int Player::OnUpdate()
{

	return 0;
}

void Player::OnDraw()
{
	DrawRectangle(position.x - size.x / 2, position.y - size.y / 2, size.x, size.y, BLACK);
	for (int i = 0; i < life; i++)
	{
		DrawRectangle(20 + 40 * i, GetScreenHeight() - 30, 35, 10, LIGHTGRAY);
	}
}

float Player::GetPositionX()
{
	return position.x;
}

float Player::GetPositionY()
{
	return position.y;
}

float Player::GetWidth()
{
	return size.x;
}

float Player::GetHeight()
{
	return size.y;
}