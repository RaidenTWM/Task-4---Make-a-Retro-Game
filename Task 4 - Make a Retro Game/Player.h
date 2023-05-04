#pragma once
#include "raylib.h"
class Player
{
protected:
	Vector2 position;
	Vector2 size;
public:
	Player();
	int life;
	int OnUpdate();
	void OnDraw();
	float GetPositionX();
	float GetPositionY();
	float GetWidth();
	float GetHeight();
};

