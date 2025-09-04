#include "level.h"

void Level::LoadLevel(int levelID)
{
	obstacles.clear();

    if (levelID == 0) {
        obstacles.push_back({ {0, 400, 800, 50}, true });
        obstacles.push_back({ {400, 370, 150, 50}, true });
        obstacles.push_back({ {200, 320, 100, 20}, true });
        obstacles.push_back({ {400, 250, 150, 20}, true });
    }
    else if (levelID == 1) {
        obstacles.push_back({ {0, 450, 1000, 50}, true });
        obstacles.push_back({ {150, 370, 80, 20}, true });
        obstacles.push_back({ {300, 280, 120, 20}, true });
        obstacles.push_back({ {500, 200, 50, 20}, true });
        obstacles.push_back({ {600, 140, 150, 20}, true });
    }
}

void Level::DrawLevel()
{
    for (const auto& obs : obstacles)
    {
        DrawRectangleRec(obs.rect, GRAY);
    }
}