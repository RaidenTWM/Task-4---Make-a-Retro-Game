#pragma once
#include "raylib.h"
#include "Game.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
class Game
{
private:
    int playerPoints = 0;
    int lives = 0;
    Texture2D background;
    Ball* ball;
    Player* player;
    Brick* brick[Brick::LINES_OF_BRICKS][Brick::BRICKS_PER_LINE];
    bool gameOver = false;
    bool victory = false;
    int score = 0;
    int* diff;
public:
    Game();
    void Shutdown();
    void Update();
    void Draw();
    void Init(int* difficulty);
    ~Game();
};