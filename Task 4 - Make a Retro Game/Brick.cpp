#include "Brick.h"
#include "raylib.h"

Vector2 Brick::brickSize;
Brick::Brick(int i, int j)
{
	//The size of the brick scales to the screen height
	Brick::brickSize = { (float)(GetScreenWidth() / BRICKS_PER_LINE - 5), (float)GetScreenHeight() / 18};
	position = { 50 + j * brickSize.x + brickSize.x / 2, i * brickSize.y + 90 };
	active = true;
	//Loads
	if (i == 0) { brickSprite = LoadTexture("Images/White_Brick.png"); }
	else if (i == 1) { brickSprite = LoadTexture("Images/Red_Brick.png"); }
	else if (i == 2) { brickSprite = LoadTexture("Images/Yellow_Brick.png"); }
	else if (i == 3) { brickSprite = LoadTexture("Images/Blue_Brick.png"); }
	else { brickSprite = LoadTexture("Images/Green_Brick.png"); }
	brickSprite.width = brickSize.x;
	brickSprite.height = brickSize.y;
}

float Brick::GetPositionX()
{
	return position.x;
}

float Brick::GetPositionY()
{
	return position.y;
}

bool Brick::IsAlive()
{
	return active;
}

void Brick::Kill()
{
	active = false;
}

void Brick::Unload()
{
	UnloadTexture(brickSprite);
}
