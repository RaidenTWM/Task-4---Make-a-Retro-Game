#pragma once
#include "raylib.h"
class Brick
{
protected:
	Vector2 position;
	bool active;
public:
	Texture2D brickSprite;
	static const int BRICKS_PER_LINE = 20;
	static const int LINES_OF_BRICKS = 5;
	static Vector2 brickSize;
	Brick(int i, int j);
	float GetPositionX();
	float GetPositionY();
	bool IsAlive();
	void Kill();
	void Unload();
};