#include "raylib.h"
#include "Game.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

Ball* ball;
Player* player;
Brick* brick[5][20];
bool gameOver = false;
void Game::Init()
{
    ball = new Ball();
    player = new Player();
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            brick[i][j] = new Brick();
        }
    }
}

Game::Game()
{
}

Game::~Game() {
}

void Game::Update()
{
    player->OnUpdate();
    ball->OnUpdate(player, brick);
    if (player->life <= 0) { gameOver = true; }
    else
    {
        gameOver = true;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (brick[i][j]->IsAlive()) gameOver = false;
            }
        }
    }
    if (gameOver && IsKeyPressed(KEY_ENTER))
    {
        Init();
        gameOver = false;
    }
}

void Game::Shutdown()
{
    delete ball;
    ball = nullptr;
    delete player;
    player = nullptr;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            delete brick[i][j];
            brick[i][j] = nullptr;
        }
    }
}

void Game::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawFPS(10, 10);

    if (!gameOver)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                if (brick[i][j]->IsAlive())
                {
                    if ((i + j) % 2 == 0) DrawRectangle(brick[i][j]->GetPositionX() - (GetScreenWidth() / 20) / 2, brick[i][j]->GetPositionY() - 20, (GetScreenWidth() / 20), 40, GRAY);
                    else
                    {
                        DrawRectangle(brick[i][j]->GetPositionX() - (GetScreenWidth() / 20) / 2, brick[i][j]->GetPositionY() - 20, (GetScreenWidth() / 20), 40, DARKGRAY);
                    }
                }
            }
        }
        ball->OnDraw();
        player->OnDraw();
    }
    else
    {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);
    }
    EndDrawing();
}