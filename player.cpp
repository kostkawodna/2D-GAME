#include "player.h"
#include <raylib.h>

Player::Player()
{
    // Load dynamic animations
    AddAnimation("IDLE", "Textures/Knight/IDLE.png", 7);
    AddAnimation("WALK", "Textures/Knight/WALK.png", 8);
    AddAnimation("RUN", "Textures/Knight/RUN.png", 8);
    AddAnimation("JUMP", "Textures/Knight/JUMP.png", 5);
    AddAnimation("ATTACK", "Textures/Knight/ATTACK 1.png", 6);
    AddAnimation("DEFEND", "Textures/Knight/DEFEND.png", 6);

    // Hitbox
    hitboxOffsetX = 32;
    hitboxOffsetY = 27;
    hitboxWidth = 32;
    hitboxHeight = 35;

    // Name
    name = "Player1";
    textWidth = MeasureText(name, 10);
}

void Player::Update(const std::vector<Obstacle>& obstacles)
{
    bool moving = false;
    bool right = IsKeyDown(KEY_D);
    bool left = IsKeyDown(KEY_A);
    bool runHeld = IsKeyDown(KEY_LEFT_SHIFT);
    float speed = runHeld ? runSpeed : walkSpeed;

    // Movement input
    if (right && !isAttacking && !isDefending) { position.x += speed; facingRight = true; moving = true; }
    if (left && !isAttacking && !isDefending) { position.x -= speed; facingRight = false; moving = true; }

    // Jump
    if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_SPACE)) && isGrounded && !isAttacking && !isDefending)
        yVelocity = -10.0f;

    // Attack / defend input
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && isGrounded && !isAttacking && !isDefending)
    {
        isAttacking = true;
        SetState("ATTACK");
        currentFrame = 0;
        frameCounter = 0;
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && isGrounded && !isAttacking && !isDefending)
    {
        isDefending = true;
        SetState("DEFEND");
        currentFrame = 0;
        frameCounter = 0;
    }

    // Apply gravity and handle collisions
    yVelocity += gravity;
    position.y += yVelocity;
    HandleCollisions(obstacles);

    // Determine animation state
    if (!isGrounded) SetState("JUMP");
    else if (isAttacking) SetState("ATTACK");
    else if (isDefending) SetState("DEFEND");
    else if (moving && runHeld) SetState("RUN");
    else if (moving) SetState("WALK");
    else SetState("IDLE");

    // Animate frames
    Animate();

    // Reset attack/defend flags when animation finishes
    Animation& currentAnim = animations[state];
    if (currentFrame == currentAnim.frameCount - 1)
    {
        if (isAttacking) isAttacking = false;
        if (isDefending) isDefending = false;
    }
}

