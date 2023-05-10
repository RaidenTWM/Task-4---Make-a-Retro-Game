#pragma once
class Game
{
private:
    int playerPoints = 0;
    int lives = 0;
    Texture2D background;
public:
    Game();
    void Shutdown();
    void Update();
    void Draw();
    void Init(int* difficulty);
    ~Game();
};

