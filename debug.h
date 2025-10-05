#pragma once
#include <raylib.h>
#include <cmath>

class debug
{
public:
    void DrawCursorPos(const Camera2D& camera);
    Rectangle CreateRectangleFromMouse(Vector2 start, Vector2 end);

    // New function to handle rectangle drawing and printing
    void HandleDebugRectangle(const Camera2D& camera);

private:
    Vector2 rectStartPos;
    Rectangle debugRect = { 0, 0, 0, 0 };
    bool drawingRect = false;
};


