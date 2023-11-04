#include <raylib.h>
#include "game.h"
#include <iostream>

int main() {
    Color grey = Color{29, 29, 27, 255};
    Color yellow = Color{243, 216, 63, 255};

    int windowWidth = 750;
    int windowHeight = 700;
    int offset = 50;
    InitAudioDevice();
    InitWindow(windowWidth + offset, windowHeight + 2*offset, "C++ Space Invaders with raylib");

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");


    Game game;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMusicStream(game.music);
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines(
            (Rectangle){10, 10, 780, 780},
            0.18f,      // Roundness (radius of the rounded corners)
            20,      // Number of segments for each rounded corner
            2,       // Border thickness
            yellow   // Border color
        );

        DrawLineEx({25, 730}, {775, 730}, 3, yellow);
        game.Draw();

        if (game.run)
        {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        }else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        int x = 50;
        for(int i=0; i < game.lives; i++){
            DrawTextureV(spaceshipImage, {float(x), 745}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);

        char scoreText[10];
        sprintf(scoreText, "%05d", game.score);
        DrawTextEx(font, scoreText, {50, 40}, 34, 2, yellow);
        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        char highscoreText[10];
        sprintf(highscoreText, "%05d", game.highscore);
        DrawTextEx(font, highscoreText, {655, 40}, 34, 2, yellow);


        EndDrawing();
    }
    CloseWindow(); 
}