#pragma once
#include "entity.h"

class Minotaur : public entity
{
public:
	Minotaur();
	void Update(const std::vector<Obstacle>& obstacles) override;
};

