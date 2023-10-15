#include <raylib.h>

int main() {
    Color darkGreen = Color{20, 160, 183, 255};

    int screenWidth = 800;
    int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(darkGreen);
        EndDrawing();
    }
    CloseWindow(); 
}
