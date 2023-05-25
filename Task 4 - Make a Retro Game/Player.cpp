#include "Player.h"
 
Player::Player(int* diff)
{
	//Puts the player at the bottom middle of the screen.
	position = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() * 7 / 8 };
	//Assigns the size of the player
	size = { 120, 30 };
	//Sets the lives of the player depending on the difficulty
	if (*diff == 0) { life = 0; }
	else if (*diff == 1) { life = 5; }
	else { life = 3; }
	//Loading the sprite of the player
	playerSprite = LoadTexture("Images/Player_Sprite.png");
	playerSprite.width = size.x;
	playerSprite.height = size.y;
	//Loading the sprite of the lives
	liveSprite = LoadTexture("Images/Lives.png");
	liveSprite.width = 35;
	liveSprite.height = 10;
}

int Player::OnUpdate(float speed)
{
	//Player movement logic
	//If holding 'A', move left
	if (IsKeyDown(KEY_A)) 
	{ 
		if (fabs(speed) > 0)
		{
		position.x -= fabs(speed); 
		}
		else { position.x -= 5; }
	}
	//Stop the player from moving off the left side of the screen
	if ((position.x - size.x / 2) <= 46) { position.x = size.x / 2 + 46; }
	//If holding 'D', move right
	if (IsKeyDown(KEY_D))
	{
		if (fabs(speed) > 0)
		{
			position.x += fabs(speed);
		}
		else { position.x += 5; }
	}
	//Stop the player from moving off the right side of the screen
	if ((position.x + size.x / 2) >= GetScreenWidth() - 46) { position.x = GetScreenWidth() - size.x / 2 - 46; }

	return 0;
}

void Player::OnDraw()
{
	//Drawing the player as a texture
	DrawTextureEx(playerSprite, { position.x - (playerSprite.width / 2), position.y - (playerSprite.height / 2) }, 0, 1, WHITE);
	for (int i = 0; i < life; i++)
	{
		DrawTextureEx(liveSprite, { (float)50 + 40 * i, (float)GetScreenHeight() - 30 }, 0, 1, LIGHTGRAY);
	}
}

//Public ways to get values
float Player::GetPositionX()
{
	return position.x;
}

float Player::GetPositionY()
{
	return position.y;
}

float Player::GetWidth()
{
	return size.x;
}

float Player::GetHeight()
{
	return size.y;
}

//Unloads the sprites
void Player::Unload()
{
	UnloadTexture(playerSprite);
	UnloadTexture(liveSprite);
}