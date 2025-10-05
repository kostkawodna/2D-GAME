#pragma once
#include "entity.h"
#include "player.h"

class Player;

class Minotaur : public entity
{
public:
	Minotaur(Player& playerRef);
	void Update(const std::vector<Obstacle>& obstacles) override;

private:
	Player& player;
	int shuffleTimer = 0;
};

