#include "raylib.h"
#include "player.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "2D");

    player myPlayer;
    myPlayer.playerPos = { 350.0f, 150.0f };
    myPlayer.LoadPlayerTexture();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        myPlayer.UpdatePlayer();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawLine(0, 210, 800, 210, BLACK);
        myPlayer.DrawPlayer();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
