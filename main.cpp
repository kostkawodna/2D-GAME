#include "raylib.h"
#include "player.h"
#include "minotaur.h"
#include "automationManager.h"
#include "Level.h"
#include "debug.h"

int main()
{
    // Game window
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "2D Game");

    SetTargetFPS(60);

    // Debug
    debug debugSystem;
    bool isDebug = false;

    // Player
    Player myPlayer;
    myPlayer.position = { 350.0f, 150.0f };

    // Camera
    Camera2D camera = { 0 };
    camera.target = myPlayer.position;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Other entities:

    // Minotaur
    Minotaur minotaur(myPlayer);
    minotaur.position = { 450.0f, 50.0f };

    // Automation
    AutomationManager automation;
    Vector2 tempCords = myPlayer.position;

    // Level
    Level currentLevel;
    currentLevel.LoadLevel(0);

    while (!WindowShouldClose())
    {
        // Automation events
        if (IsKeyPressed(KEY_F1))
        {
            if (!automation.IsRecording())
                tempCords = myPlayer.position;
            automation.ToggleRecording();
        }

        if (IsKeyPressed(KEY_F2))
        {
            myPlayer.position = tempCords;
            automation.TogglePlayback();
        }

        if (IsKeyPressed(KEY_F3))
        {
            automation.ResetScene();
            myPlayer.position = tempCords; // reset player
        }

        if (IsKeyPressed(KEY_F4))
        {
            isDebug = !isDebug;
        }

        automation.Update();

        // Update and camera
        myPlayer.Update(currentLevel.GetObstacles());
        minotaur.Update(currentLevel.GetObstacles());

        camera.target = { myPlayer.position.x + myPlayer.frameRec.width / 2,
                         myPlayer.position.y + myPlayer.frameRec.height / 2 };

        camera.zoom = expf(logf(camera.zoom) + (GetMouseWheelMove() * 0.1f));

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(camera);

        currentLevel.DrawLevel();
        minotaur.Draw(10, 20, RED);
        myPlayer.Draw(20, 10, BLUE);

        if (isDebug)
        {
            debugSystem.HandleDebugRectangle(camera);
        }
 
        EndMode2D();

        // Draw player coordinates
        DrawText(TextFormat("X: %.2f", myPlayer.position.x), 705, 10, 20, BLUE);
        DrawText(TextFormat("Y: %.2f", myPlayer.position.y), 705, 30, 20, BLUE);

        // Automation text
        if (automation.IsRecording()) DrawText("Recording...", 10, 10, 20, RED);
        if (automation.IsPlaying())   DrawText("Playing...", 10, 10, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
