#include "raylib.h"
#include "player.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "2D");

    player myPlayer;
    myPlayer.playerPos = { 350.0f, 280.0f };
    myPlayer.LoadPlayerTexture();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        myPlayer.UpdatePlayer();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        myPlayer.DrawPlayer();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
