#include <raylib.h>
#include "spaceship.h"
#include "obstacle.h"

int main() {
    Color grey = Color{29, 29, 27, 255};

    int windowWidth = 750;
    int windowHeight = 700;
    InitWindow(windowWidth, windowHeight, "C++ Space Invaders");

    Spaceship spaceship = Spaceship();
    Obstacle obstacle = Obstacle(100, 100);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        spaceship.Update();
        for(Laser& laser: spaceship.lasers){
            laser.Update();
        }

        BeginDrawing();
        ClearBackground(grey);
        spaceship.Draw();
        obstacle.Draw();
        for(Laser& laser: spaceship.lasers){
            laser.Draw();
        }
        EndDrawing();
    }
    CloseWindow(); 
}