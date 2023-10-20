#include <raylib.h>
#include "game.h"

int main() {
    Color grey = Color{29, 29, 27, 255};

    int windowWidth = 750;
    int windowHeight = 700;
    InitWindow(windowWidth, windowHeight, "C++ Space Invaders");

    Game game;
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        game.Draw();
        EndDrawing();
    }
    CloseWindow(); 
}