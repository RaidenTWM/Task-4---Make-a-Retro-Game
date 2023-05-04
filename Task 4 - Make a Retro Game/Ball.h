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
public:
	Ball();
	int OnUpdate(Player* player, Brick* brick[5][20]);
	void OnDraw();
};

