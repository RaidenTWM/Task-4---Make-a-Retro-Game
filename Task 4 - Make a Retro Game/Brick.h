#pragma once
#include "raylib.h"
class Brick
{
protected:
	Vector2 position;
	bool active;
public:
	static const int BRICKS_PER_LINE = 20;
	static const int LINES_OF_BRICKS = 5;
	static const int BRICK_POINTS = 10;
	static const Vector2 brickSize;
	Brick(int i, int j);
	float GetPositionX();
	float GetPositionY();
	bool IsAlive();
	void Kill();
};

