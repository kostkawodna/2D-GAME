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
        {AnimationState::JUMP, "JUMP.png", 5}
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

void player::UpdatePlayer()
{
    bool isMoving = false;


    if (IsKeyDown(KEY_D))
    {
        playerPos.x += playerSpeed.x;
        isMoving = true;
        facingRight = true;
    }
    if (IsKeyDown(KEY_A))
    {
        playerPos.x -= playerSpeed.x;
        isMoving = true;
        facingRight = false;
    }
    if (IsKeyDown(KEY_W) && isGrounded)
    {
        yVelocity = -10.0f;
        isGrounded = false;
    }
    if (IsKeyDown(KEY_LEFT))
    {

    }

    yVelocity += gravity;
    playerPos.y += yVelocity;

    // TEMPORARY simple ground collision
    float floorHeight = 150.0f; // replace with actual platform logic later
    if (playerPos.y >= floorHeight)
    {
        playerPos.y = floorHeight;
        yVelocity = 0;
        isGrounded = true;
    }

    if (!isGrounded)
        state = AnimationState::JUMP;
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
        if (currentFrame >= currentAnim.frameCount)
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
    playerHitBox = { playerPos.x + 32, playerPos.y + 28, 32, 35};

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
