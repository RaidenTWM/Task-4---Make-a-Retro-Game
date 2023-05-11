#include <iostream>
#include "raylib.h"
#include "Game.h"
int main()
{
    //Creates a new Game class variable called game.
    Game* game = new Game();
    int difficulty = -1;
    while (difficulty < 0 || difficulty > 2)
    {
        std::cout << "What difficulty do you want to play with?\n0 = Easy\n1 = Normal\n2 = Hard\nDifficulty: ";
        std::cin >> difficulty;
    }

    //Sets the size of the game window and the name of the window.
    InitWindow(1280, 720, "Arkanoid");

    InitAudioDevice();

    //Initialises the game to run the init code found in the Game.cpp.
    game->Init(&difficulty);

    //While the window is open..keep updating and drawing whatever is being requested from
    //  other classes.
    while (!WindowShouldClose())
    {
        if (difficulty == 2) { SetTargetFPS(120); }
        else { SetTargetFPS(60); }
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