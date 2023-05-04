#pragma once
#include "raylib.h"
class Brick
{
protected:
	Vector2 position;
	Vector2 brickSize;
	bool active;
public:
	Brick();
	float GetPositionX();
	float GetPositionY();
	bool IsAlive();
	void Kill();
};

