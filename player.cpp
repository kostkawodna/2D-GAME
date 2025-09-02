#include "player.h"

void player::LoadPlayerTexture()
{
    struct AnimationLoadInfo
    {
        AnimationState state;
        const char* fileName;
        int frames;
    };

    AnimationLoadInfo animationsToLoad[] = {
        {AnimationState::IDLE, "IDLE.png", 7},
        {AnimationState::WALK, "WALK.png", 8},
        {AnimationState::RUN, "RUN.png", 8},
        {AnimationState::JUMP, "JUMP.png", 5},
        {AnimationState::ATTACK1, "ATTACK 1.png", 6},
        {AnimationState::DEFEND, "DEFEND.png", 6}
    };

    for (const auto& info : animationsToLoad)
    {
        std::string fullPath = "player_model/";
        fullPath += info.fileName;

        Animation anim;
        anim.texture = LoadTexture(fullPath.c_str());
        anim.frameCount = info.frames;

        animations[info.state] = anim;

        if (info.state == state)
        {
            frameRec = { 0.0f, 0.0f, (float)anim.texture.width / anim.frameCount, (float)anim.texture.height };
            currentFrame = 0;
        }
    }

}

void player::HandleCollisions(const std::vector<Obstacle>& obstacles)
{
    // Update hitbox
    playerHitBox = { playerPos.x + hitboxOffsetX,
                     playerPos.y + hitboxOffsetY,
                     hitboxWidth,
                     hitboxHeight };

    isGrounded = false;

    for (const auto& obs : obstacles)
    {
        if (!obs.solid) continue;

        if (CheckCollisionRecs(playerHitBox, obs.rect))
        {
            // Falling onto platform
            if (yVelocity > 0 && (playerHitBox.y + playerHitBox.height - yVelocity) <= obs.rect.y)
            {
                playerPos.y = obs.rect.y - hitboxOffsetY - hitboxHeight;
                yVelocity = 0;
                isGrounded = true;
            }
            // Hitting head
            else if (yVelocity < 0 && (playerHitBox.y - yVelocity) >= (obs.rect.y + obs.rect.height))
            {
                playerPos.y = obs.rect.y + obs.rect.height - hitboxOffsetY;
                yVelocity = 0;
            }

            // horizontal collision handler here :D
        }
    }
}

void player::UpdatePlayer(const std::vector<Obstacle>& obstacles)
{

    // Handle inputs
    bool isMoving = false;
    bool movingRight = IsKeyDown(KEY_D);
    bool movingLeft = IsKeyDown(KEY_A);
    bool shiftHeld = IsKeyDown(KEY_LEFT_SHIFT);
    bool isRunning = shiftHeld && (movingRight || movingLeft);

    float actualSpeed = isRunning ? runSpeed : walkSpeed;

    if (movingRight && !isAttacking && !isDefending)
    {
        playerPos.x += actualSpeed;
        isMoving = true;
        facingRight = true;
    }
    if (movingLeft && !isAttacking && !isDefending)
    {
        playerPos.x -= actualSpeed;
        isMoving = true;
        facingRight = false;
    }
    if ((IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_W)) && isGrounded && !isAttacking && !isDefending)
    {
        yVelocity = -10.0f;
        isGrounded = false;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !isAttacking && isGrounded && !isDefending)
    {
        isAttacking = true;
        currentFrame = 0;
        frameCounter = 0;
    }
    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !isAttacking && isGrounded && !isDefending)
    {
        isDefending = true;
        currentFrame = 0;
        frameCounter = 0;
    }
        
    isRunning = shiftHeld && (movingRight || movingLeft);

    // Gravity
    yVelocity += gravity;
    playerPos.y += yVelocity;

    // Collisions
    HandleCollisions(obstacles);

    // Animations
    if (!isGrounded)
        state = AnimationState::JUMP;
    else if (isAttacking)
        state = AnimationState::ATTACK1;
    else if (isDefending)
        state = AnimationState::DEFEND;
    else if (isRunning && isMoving)
        state = AnimationState::RUN;
    else if (isMoving)
        state = AnimationState::WALK;
    else
        state = AnimationState::IDLE;

    // Animation frame update
    Animation& currentAnim = animations[state];
    frameRec.width = (float)currentAnim.texture.width / currentAnim.frameCount;
    frameRec.height = (float)currentAnim.texture.height;

    frameCounter++;
    if (frameCounter >= (60 / 12))
    {
        frameCounter = 0;
        currentFrame++;

        if (state == AnimationState::ATTACK1 && currentFrame >= currentAnim.frameCount)
        {
            isAttacking = false;
            currentFrame = 0;
        }
        if (state == AnimationState::DEFEND && currentFrame >= currentAnim.frameCount)
        {
            isDefending = false;
            currentFrame = 0;
        }
        else if (currentFrame >= currentAnim.frameCount)
            currentFrame = 0;
    }

    frameRec.x = (float)currentFrame * frameRec.width;
    frameRec.y = 0;
}

Animation& player::GetCurrentAnimation()
{
    return animations[state];
}

void player::DrawPlayer()
{
    Animation& currentAnim = GetCurrentAnimation();
    DrawText(playerName, playerHitBox.x - textWidth / 2 + playerHitBox.width / 2, playerHitBox.y - 20, 10, PINK); //Draw Player name

    if (facingRight)
        DrawTextureRec(currentAnim.texture, frameRec, playerPos, WHITE);
    else
    {
        Rectangle flippedRec = frameRec;
        flippedRec.width *= -1;

        DrawTextureRec(currentAnim.texture, flippedRec, playerPos, WHITE);
    }

    DrawRectangleLines(playerHitBox.x, playerHitBox.y, playerHitBox.width, playerHitBox.height, RED); //hitbox
    DrawRectangleLines(playerPos.x, playerPos.y, frameRec.width, frameRec.height, WHITE); //size of animated frame
}

