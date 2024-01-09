#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "Tetris!");
    SetTargetFPS(60); //define frames per second

    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

    Game game = Game(); //initialize with the default constructor

    //GAME LOOP ------------------------
    while(WindowShouldClose() == false)
    {
        game.HandleInput();
        
        //speed of falling blocks is 0.3s initially
        if(EventTriggered(game.speed))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "Level: ", {330, 15}, 30, 2, WHITE);
        char levelNum[10];
        sprintf(levelNum, "%d", game.level);
        DrawTextEx(font, levelNum, {430, 15}, 30, 2, WHITE);

        DrawTextEx(font, "Score", {330, 55}, 30, 2, WHITE);
        DrawRectangleRounded({330, 95, 150, 60}, 0.3, 6, lightBlue);

        //to print the score, centered in the box
        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 scoreTextSize = MeasureTextEx(font, scoreText, 30, 2);
        DrawTextEx(font, scoreText, {330 + (150 - scoreTextSize.x)/2, 105}, 30, 2, WHITE);

        DrawTextEx(font, "Next", {330, 165}, 30, 2, WHITE);
        DrawRectangleRounded({330, 205, 150, 150}, 0.1, 6, lightBlue);

        DrawTextEx(font, "Hold", {330, 365}, 30, 2, WHITE);
        DrawRectangleRounded({330, 405, 150, 150}, 0.1, 6, lightBlue);

        if(game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {330, 565}, 30, 2, WHITE);
        }

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}