#include <raylib.h>
#include "spaceship.h"
#include "laser.h"

int main() {
    Color grey = Color{29, 29, 27, 255};

    int windowWidth = 750;
    int windowHeight = 700;
    InitWindow(windowWidth, windowHeight, "C++ Space Invaders");

    Spaceship spaceship = Spaceship();
    Laser laser = Laser({100, 100}, -6);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        spaceship.Update();
        laser.Update();
        BeginDrawing();
        ClearBackground(grey);
        spaceship.Draw();
        laser.Draw();
        EndDrawing();
    }
    CloseWindow(); 
}