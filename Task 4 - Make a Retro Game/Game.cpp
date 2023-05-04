#include "raylib.h"
#include "Game.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

Ball* ball;
Player* player;
Brick* brick[Brick::LINES_OF_BRICKS][Brick::BRICKS_PER_LINE];
bool gameOver = false;
int score = 0;
void Game::Init()
{
    ball = new Ball();
    player = new Player();
    for (int i = 0; i < Brick::LINES_OF_BRICKS; i++)
    {
        for (int j = 0; j < Brick::BRICKS_PER_LINE; j++)
        {
            brick[i][j] = new Brick(i, j);
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
    ball->OnUpdate(player, brick, &score);
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
        for (int i = 0; i < Brick::LINES_OF_BRICKS; i++)
        {
            for (int j = 0; j < Brick::BRICKS_PER_LINE; j++)
            {
                if (brick[i][j]->IsAlive())
                {
                    if (i == 0)
                    {
                        DrawRectangle(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, DARKGRAY);
                        DrawRectangleLines(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, BLACK);
                    }
                    else if (i == 1)
                    {
                        DrawRectangle(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, RED);
                        DrawRectangleLines(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, BLACK);
                    }
                    else if (i == 2)
                    {
                        DrawRectangle(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, YELLOW);
                        DrawRectangleLines(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, BLACK);
                    }
                    else if (i == 3)
                    {
                        DrawRectangle(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, BLUE);
                        DrawRectangleLines(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, BLACK);
                    }
                    else if (i == 4)
                    {
                        DrawRectangle(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, GREEN);
                        DrawRectangleLines(brick[i][j]->GetPositionX() - Brick::brickSize.x / 2, brick[i][j]->GetPositionY() - Brick::brickSize.y / 2, Brick::brickSize.x, Brick::brickSize.y, BLACK);
                    }
                }
            }
        }
        ball->OnDraw();
        player->OnDraw();
        DrawText(TextFormat("SCORE: %05i", score), 10, GetScreenHeight() - 20, 20, GRAY);
    }
    else
    {
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 30) / 2, GetScreenHeight() / 2 - 50, 30, GRAY);
    }
    EndDrawing();
}