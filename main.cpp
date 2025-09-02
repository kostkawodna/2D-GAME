#include "raylib.h"
#include "player.h"
#include "automationManager.h"
#include "Level.h"

int main(void)
{
    // Game window
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "2D");

    // Init player
    player myPlayer;
    myPlayer.playerPos = { 350.0f, 150.0f };
    myPlayer.LoadPlayerTexture();

    // Init camera
    Camera2D camera = { 0 };
    camera.target = { myPlayer.playerPos.x, myPlayer.playerPos.y };
    camera.offset = { screenWidth / 2.0f - 2, screenHeight / 2.0f - 30 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Init automation events
    AutomationManager automation;

    // Init levels
    Level currentLevel;
    currentLevel.LoadLevel(0);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // Automation events
        if (IsKeyPressed(KEY_B)) automation.ToggleRecording();
        if (IsKeyPressed(KEY_N)) automation.TogglePlayback();
        if (IsKeyPressed(KEY_M)) {
            automation.ResetScene();
            myPlayer.playerPos = { 400, 280 }; // reset player state
        }
        automation.Update();

        // Update player and camera
        myPlayer.UpdatePlayer(currentLevel.GetObstacles());
        camera.target = { myPlayer.playerPos.x + myPlayer.frameRec.width / 2, myPlayer.playerPos.y + myPlayer.frameRec.height / 2 };
        camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));

        // Viewport
        BeginDrawing();
        ClearBackground(DARKGRAY);
        BeginMode2D(camera);
        currentLevel.DrawLevel();
        myPlayer.DrawPlayer();

        EndMode2D();
        EndDrawing();

        // Automation events text
        if (automation.IsRecording()) DrawText("Recording...", 10, 10, 20, RED);
        if (automation.IsPlaying())   DrawText("Playing...", 10, 10, 20, GREEN);
    }

    CloseWindow();

    return 0;
}
