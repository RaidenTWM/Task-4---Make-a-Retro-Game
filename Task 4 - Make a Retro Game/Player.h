#pragma once
#include "raylib.h"
class Player
{
protected:
	Vector2 position;
	Vector2 size;
	Texture2D playerSprite;
public:
	Player();
	int life;
	int OnUpdate(float speed);
	void OnDraw();
	float GetPositionX();
	float GetPositionY();
	float GetWidth();
	float GetHeight();
	void Unload();
};

