#include "raylib.h"
#include "Game.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"

//Pre-initialising all the variables required
Ball* ball;
Player* player;
Brick* brick[Brick::LINES_OF_BRICKS][Brick::BRICKS_PER_LINE];
bool gameOver = false;
int score = 0;
Texture2D background;
void Game::Init()
{
    ball = new Ball();
    player = new Player();
    //Creating the rows of bricks required for the game
    for (int i = 0; i < Brick::LINES_OF_BRICKS; i++)
    {
        //Creating the columns of bricks required for the game
        for (int j = 0; j < Brick::BRICKS_PER_LINE; j++)
        {
            brick[i][j] = new Brick(i, j);
        }
    }
    background = LoadTexture("Images/Background.png");
    background.width = GetScreenWidth();
    background.height = GetScreenHeight();
}

//Default constructor
Game::Game()
{
}

//Default destructor
Game::~Game() {
}

//Running through this for each frame of the game
void Game::Update()
{
    //Updating the player
    player->OnUpdate(ball->GetSpeed().y);
    //Updating the ball
    ball->OnUpdate(player, brick, &score);
    //Checks to see if the player has any lives left...
    if (player->life <= 0) { gameOver = true; }
    //...else it checks to see if there are any bricks still active.
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
    //If the game is over, the player can reset it by pressing ENTER
    if (gameOver && IsKeyPressed(KEY_ENTER))
    {
        Init();
        gameOver = false;
        score = 0;
    }
}

//Shutdown procedure. Deletes and makes everything a nullptr.
void Game::Shutdown()
{
    UnloadTexture(background);
    ball->Unload();
    delete ball;
    ball = nullptr;
    delete player;
    player = nullptr;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            brick[i][j]->Unload();
            delete brick[i][j];
            brick[i][j] = nullptr;
        }
    }
}

//Drawing the game window.
void Game::Draw()
{
    BeginDrawing();

    //White background
    //ClearBackground(RAYWHITE);
    DrawTextureEx(background, { (float)GetScreenWidth() / 2 - background.width / 2, (float)GetScreenHeight() / 2 - background.height / 2 }, 0, 1, WHITE);

    //Draws the fps in the top left
    DrawFPS(10, 10);

    //If the game isn't over
    if (!gameOver)
    {
        for (int i = 0; i < Brick::LINES_OF_BRICKS; i++)
        {
            for (int j = 0; j < Brick::BRICKS_PER_LINE; j++)
            {
                //Draws all of the living bricks (Coloured by row, with black outlines on them all)
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
        //Draws the ball and player
        ball->OnDraw();
        player->OnDraw();
        //Writes a score in the bottom left
        DrawText(TextFormat("SCORE: %05i", score), 10, GetScreenHeight() - 20, 20, GRAY);
    }
    else
    {
        //If the game IS over, display the text instead and don't draw anything else.
        DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 30) / 2, GetScreenHeight() / 2 - 50, 30, GRAY);
    }
    EndDrawing();
}