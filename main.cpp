#include <raylib.h>
#include "game.h"

int main() {
    Color grey = Color{29, 29, 27, 255};

    int windowWidth = 750;
    int windowHeight = 700;
    InitWindow(windowWidth, windowHeight, "C++ Space Invaders");

    Game game = Game();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        game.spaceship.Update();
        for(Laser& laser: game.spaceship.lasers){
            laser.Update();
        }

        BeginDrawing();
        ClearBackground(grey);
        game.spaceship.Draw();

        for(Obstacle& obstacle: game.obstacles)
        {
            obstacle.Draw();
        }

        for(Laser& laser: game.spaceship.lasers){
            laser.Draw();
        }


        EndDrawing();
    }
    CloseWindow(); 
}