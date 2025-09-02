#pragma once
#include "raylib.h"
#include <vector>

struct Obstacle {
	Rectangle rect;
	bool solid;
};

class Level
{
public:
	void LoadLevel(int levelID);
	void DrawLevel();
	const std::vector<Obstacle>& GetObstacles() const { return obstacles; }

private:
	std::vector<Obstacle> obstacles;
};

