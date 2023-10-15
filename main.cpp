#include <raylib.h>
#include "spaceship.h"

int main() {
    Color grey = Color{29, 29, 27, 255};

    int screenWidth = 750;
    int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "C++ Space Invaders");

    Spaceship spaceship = Spaceship();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        spaceship.Update();

        BeginDrawing();
        ClearBackground(grey);
        spaceship.Draw();
        EndDrawing();
    }
    CloseWindow(); 
}