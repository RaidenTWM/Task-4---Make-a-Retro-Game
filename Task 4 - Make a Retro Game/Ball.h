#pragma once
#include "raylib.h"
#include "Player.h"
#include "Brick.h"
class Ball
{
protected:
	Vector2 position;
	Vector2 speed;
	int radius;
	bool active;
	Sound hit;
	Sound death;
public:
	Ball();
	int OnUpdate(Player* player, Brick* brick[Brick::LINES_OF_BRICKS][Brick::BRICKS_PER_LINE], int* score);
	void OnDraw();
};

