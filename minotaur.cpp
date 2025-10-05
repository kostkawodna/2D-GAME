#include "minotaur.h"

Minotaur::Minotaur()
{
    AddAnimation("IDLE", "Textures/Minotaur/IDLE.png", 16);
    AddAnimation("WALK", "Textures/Minotaur/WALK.png", 12);
    AddAnimation("ATTACK", "Textures/Minotaur/ATTACK.png", 16);

    // Hitbox
    hitboxOffsetX = 104;
    hitboxOffsetY = 33;
    hitboxWidth = 91;
    hitboxHeight = 109;

    name = "Minotaur";
    textWidth = MeasureText(name, 10);

    SetState("IDLE");

}

void Minotaur::Update(const std::vector<Obstacle>& obstacles)
{
    yVelocity += gravity;
    position.y += yVelocity;

    HandleCollisions(obstacles);
    Animate(12);
}