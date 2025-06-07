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

    // state switch
    if (isMoving)
    {
        state = AnimationState::WALK;
    }
    else
    {
        state = AnimationState::IDLE;
    }

    // update frame of animation
    Animation& currentAnim = animations[state];

    frameRec.width = (float)currentAnim.texture.width / currentAnim.frameCount;
    frameRec.height = (float)currentAnim.texture.height;

    frameCounter++;
    if (frameCounter >= (60 / 12))  // 12 FPS animation speed
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

    if(facingRight)
        DrawTextureRec(currentAnim.texture, frameRec, playerPos, WHITE);
    else
    {
        Rectangle flippedRec = frameRec;
        flippedRec.width *= -1;

        DrawTextureRec(currentAnim.texture, flippedRec, playerPos, WHITE);
    }
}
