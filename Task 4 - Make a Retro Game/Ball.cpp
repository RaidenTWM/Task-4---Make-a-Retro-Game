#include "Ball.h"
#include "math.h"
#include "raylib.h"

Ball::Ball()
{
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() * 7 / 8 - 30 };
	speed = { 0, 0 };
	radius = 15;
	active = false;
	hit = LoadSound("Sounds/Brick_Hit.wav");
	death = LoadSound("Sounds/Death.wav");
	ballSprite = LoadTexture("Images/Ball_Sprite.png");
	ballSprite.width = radius;
	ballSprite.height = radius;
}

Vector2 Ball::GetSpeed()
{
	return speed;
}
int Ball::OnUpdate(Player* player, Brick* brick[Brick::LINES_OF_BRICKS][Brick::BRICKS_PER_LINE], int* score)
{
	if (speed.y > 15) { speed.y = 15; }
	if (speed.y < -15) { speed.y = -15; }
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
	if (((position.x + radius) >= GetScreenWidth() - 46) || ((position.x - radius) <= 46)) { speed.x *= -1; }
	if ((position.y - radius) <= 20) { speed.y *= -1; *score += 5;; }
	if ((position.y + radius) >= GetScreenHeight())
	{
		speed = { 0, 0 };
		active = false;
		player->life--;
		PlaySound(death);
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
	for (int i = 0; i < Brick::LINES_OF_BRICKS; i++)
	{
		for (int j = 0; j < Brick::BRICKS_PER_LINE; j++)
		{
			if (brick[i][j]->IsAlive())
			{
				//Hit below
				if (((position.y - radius) <= (brick[i][j]->GetPositionY() + Brick::brickSize.y / 2)) && ((position.y - radius) > (brick[i][j]->GetPositionY() + Brick::brickSize.y / 2 + speed.y)) && ((fabs(position.x - brick[i][j]->GetPositionX())) < (Brick::brickSize.x / 2 + radius * 2 / 3)) && (speed.y < 0))
				{
					brick[i][j]->Kill();
					speed.y *= -1.005;
					*score += 100;
					PlaySound(hit);
				}
				//Hit above
				if (((position.y + radius) >= (brick[i][j]->GetPositionY() - Brick::brickSize.y / 2)) && ((position.y + radius) < (brick[i][j]->GetPositionY() - Brick::brickSize.y / 2 + speed.y)) && ((fabs(position.x - brick[i][j]->GetPositionX())) < (Brick::brickSize.x / 2 + radius * 2 / 3)) && (speed.y > 0))
				{
					brick[i][j]->Kill();
					speed.y *= -1.005;
					*score += 100;
					PlaySound(hit);
				}
				//Hit left
				if (((position.x + radius) >= (brick[i][j]->GetPositionX() - Brick::brickSize.x / 2)) && ((position.x + radius) < (brick[i][j]->GetPositionX() - Brick::brickSize.x / 2 + speed.x)) && ((fabs(position.y - brick[i][j]->GetPositionY())) < (Brick::brickSize.y / 2 + radius * 2 / 3)) && (speed.x > 0))
				{
					brick[i][j]->Kill();
					speed.x *= -1.005;
					*score += 100;
					PlaySound(hit);
				}
				//Hit right
				if (((position.x - radius) <= (brick[i][j]->GetPositionX() + Brick::brickSize.x / 2)) && ((position.x - radius) > (brick[i][j]->GetPositionX() + Brick::brickSize.x / 2 + speed.x)) && ((fabs(position.y - brick[i][j]->GetPositionY())) < (Brick::brickSize.y / 2 + radius * 2 / 3)) && (speed.x < 0))
				{
					brick[i][j]->Kill();
					speed.x *= -1.050;
					*score += 100;
					PlaySound(hit);
				}

			}
		}
	}
	return 0;
}
void Ball::OnDraw()
{
	DrawTextureEx(ballSprite, { position.x - (ballSprite.width / 2), position.y - (ballSprite.height / 2) }, 0, 1, WHITE);
	//DrawCircle(position.x, position.y, radius, MAROON);
}

void Ball::Unload()
{
	UnloadTexture(ballSprite);
}