#include "Ball.h"
#include "math.h"
#include "raylib.h"

Ball::Ball()
{
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() * 7 / 8 - 30 };
	speed = { 0, 0 };
	radius = 7;
	active = false;
}
int Ball::OnUpdate(Player* player, Brick* brick[5][20])
{
	//Ball launching logic
	if (!active)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			active = true;
			speed = { 0, -5 };
		}
	}

	//Ball movement logic
	if (active)
	{
		position.x += speed.x;
		position.y += speed.y;
	}
	else
	{
		position = { player->GetPositionX(), (float)GetScreenHeight() * 7 / 8 - 30 };
	}

	//Collision logic: ball vs walls
	if (((position.x + radius) >= GetScreenWidth()) || ((position.x - radius) <= 0)) { speed.x *= -1; }
	if ((position.y - radius) <= 0) { speed.y *= -1; }
	if ((position.y + radius) >= GetScreenHeight())
	{
		speed = { 0, 0 };
		active = false;
		player->life--;
	}

	//Collision logic: ball vs player
	if (CheckCollisionCircleRec(position, radius, { player->GetPositionX() - player->GetWidth() / 2, player->GetPositionY() - player->GetHeight() / 2, player->GetWidth(), player->GetHeight() }))
	{
		if (speed.y > 0)
		{
			speed.y *= -1;
			speed.x = (position.x - player->GetPositionX()) / (player->GetWidth() / 2) * 5;
		}
	}

	//Collision logic: ball vs brick
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (brick[i][j]->IsAlive())
			{
				//Hit below
				if (((position.y - radius) <= (brick[i][j]->GetPositionY() + 20)) && ((position.y - radius) > (brick[i][j]->GetPositionY() + 20 + speed.y)) && ((fabs(position.x + brick[i][j]->GetPositionX())) < ((GetScreenWidth() / 20) / 2 + radius * 2 / 3)) && (speed.y < 0))
				{
					brick[i][j]->Kill();
					speed.y *= -1;
				}
				//Hit above
				else if (((position.y + radius) >= (brick[i][j]->GetPositionY() - 20)) && ((position.y + radius) < (brick[i][j]->GetPositionY() - 20 + speed.y)) && ((fabs(position.x - brick[i][j]->GetPositionX())) < ((GetScreenWidth() / 20) / 2 + radius * 2 / 3)) && (speed.y > 0))
				{
					brick[i][j]->Kill();
					speed.y *= -1;
				}
				//Hit left
				else if (((position.x + radius) >= (brick[i][j]->GetPositionX() - 20)) && ((position.x + radius) < (brick[i][j]->GetPositionX() - (GetScreenWidth() / 20) / 2 + speed.x)) && ((fabs(position.y - brick[i][j]->GetPositionY())) < (20 + radius * 2 / 3)) && (speed.x > 0))
				{
					brick[i][j]->Kill();
					speed.x *= -1;
				}
				//Hit right
				else if (((position.x - radius) <= (brick[i][j]->GetPositionX() + 20)) && ((position.x - radius) > (brick[i][j]->GetPositionX() + (GetScreenWidth() / 20) / 2 + speed.x)) && ((fabs(position.y - brick[i][j]->GetPositionY())) < (20 + radius * 2 / 3)) && (speed.x < 0))
				{
					brick[i][j]->Kill();
					speed.x *= -1;
				}

			}
		}
	}

	return 0;
}
void Ball::OnDraw()
{
	DrawCircle(position.x, position.y, radius, MAROON);
}