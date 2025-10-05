#pragma once
#include "entity.h"

class Player : public entity
{
public:
    Player(); // Constructor loads animations and sets hitbox

    // Override Update for player-specific behavior (input, attack, defend)
    void Update(const std::vector<Obstacle>& obstacles) override;

private:
    // Player-specific stats
    int health = 100;

    // Combat states
    bool isAttacking = false;
    bool isDefending = false;

    // Movement speeds
    float walkSpeed = 2.0f;
    float runSpeed = 4.0f;
};
