#include <iostream>
#include "raylib.h"
#include "Game.h"
int main()
{
    //Creates a new Game class variable called game.
    Game* game = new Game();

    //Setting how wany frames per second the game should be running at.
    SetTargetFPS(60);
    //Sets the size of the game window and the name of the window.
    InitWindow(1280, 720, "Arkanoid");

    //Initialises the game to run the init code found in the Game.cpp.
    game->Init();

    //While the window is open..keep updating and drawing whatever is being requested from
    //  other classes.
    while (!WindowShouldClose())
    {
        game->Update();
        game->Draw();
    }

    //Calls upon the shutdown function.
    game->Shutdown();
    delete game;
    game = nullptr;

    //Closes the game.
    CloseWindow();
}