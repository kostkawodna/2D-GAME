#include "minotaur.h"

Minotaur::Minotaur(Player& playerRef) : player(playerRef)
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
    textWidth = MeasureText(name, 10) + 40;

    SetState("IDLE");
}

void Minotaur::Update(const std::vector<Obstacle>& obstacles)
{
    yVelocity += gravity;
    position.y += yVelocity;
    HandleCollisions(obstacles);

    shuffleTimer--;
    if (shuffleTimer <= 0)
    {
        int choice = GetRandomValue(0, 2);  // 0=IDLE, 1=WALK, 2=ATTACK
        switch (choice)
        {
        case 0: SetState("IDLE"); break;
        case 1: SetState("WALK"); break;
        case 2: SetState("ATTACK"); break;
        }

        // Reset timer for next shuffle
        shuffleTimer = GetRandomValue(60, 180); // 1–3 seconds again
    }

    facingRight = (player.position.x + player.hitboxOffsetX < position.x + hitboxOffsetX + hitboxWidth / 3);

    Animate(12);
}