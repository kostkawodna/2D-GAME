#include "debug.h"

void debug::DrawCursorPos(const Camera2D& camera)
{
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
    DrawText(TextFormat("Mouse: X=%.0f Y=%.0f", mouseWorldPos.x, mouseWorldPos.y),
        mouseWorldPos.x + 10, mouseWorldPos.y - 20, 10, GREEN);
    DrawCircle(mouseWorldPos.x, mouseWorldPos.y, 2, GREEN);
}

Rectangle debug::CreateRectangleFromMouse(Vector2 start, Vector2 end)
{
    Rectangle rect;
    rect.x = fminf(start.x, end.x);
    rect.y = fminf(start.y, end.y);
    rect.width = fabsf(end.x - start.x);
    rect.height = fabsf(end.y - start.y);
    return rect;
}

void debug::HandleDebugRectangle(const Camera2D& camera)
{
    // Draw mouse position
    DrawCursorPos(camera);

    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), camera);

    // Start drawing rectangle
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        rectStartPos = mouseWorld;
        drawingRect = true;
    }

    // Finish drawing rectangle
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && drawingRect)
    {
        debugRect = CreateRectangleFromMouse(rectStartPos, mouseWorld);
        drawingRect = false;

        // Print info
        TraceLog(LOG_INFO, "Hitbox Rect: x=%.1f, y=%.1f, w=%.1f, h=%.1f",
            debugRect.x, debugRect.y, debugRect.width, debugRect.height);
    }

    // Draw preview while dragging
    if (drawingRect)
    {
        Rectangle tempRect = CreateRectangleFromMouse(rectStartPos, mouseWorld);
        DrawRectangleLines(tempRect.x, tempRect.y, tempRect.width, tempRect.height, GREEN);
    }

    // Draw finalized rectangle
    if (debugRect.width > 0 && debugRect.height > 0)
    {
        DrawRectangleLines(debugRect.x, debugRect.y, debugRect.width, debugRect.height, RED);
    }
}

