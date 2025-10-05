#include "entity.h"

entity::entity()
{
    textWidth = MeasureText(name, 10);
}   

// Free textures if needed
entity::~entity()
{
    for (auto& pair : animations)
        UnloadTexture(pair.second.texture);
}

void entity::AddAnimation(const std::string& stateName, const std::string& filePath, int frames)
{
    Animation anim;
    anim.texture = LoadTexture(filePath.c_str());
    anim.frameCount = frames;
    animations[stateName] = anim;

    if (state.empty())
    {
        state = stateName;
        frameRec = { 0, 0, (float)anim.texture.width / frames, (float)anim.texture.height };
        currentFrame = 0;
        frameCounter = 0;
    }
}

void entity::SetState(const std::string& newState)
{
    if (state != newState && animations.find(newState) != animations.end())
    {
        state = newState;
        currentFrame = 0;
        frameCounter = 0;
    }
}

Animation& entity::GetCurrentAnimation()
{
    return animations[state];
}

void entity::HandleCollisions(const std::vector<Obstacle>& obstacles)
{
    // Update hitbox
    hitbox = { position.x + hitboxOffsetX,
               position.y + hitboxOffsetY,
               hitboxWidth,
               hitboxHeight };

    isGrounded = false;

    for (const auto& obs : obstacles)
    {
        if (!obs.solid) continue;

        if (CheckCollisionRecs(hitbox, obs.rect))
        {
            // Vertical collision
            if (yVelocity > 0 && (hitbox.y + hitbox.height - yVelocity) <= obs.rect.y)
            {
                // Falling onto platform
                position.y = obs.rect.y - hitboxOffsetY - hitboxHeight;
                yVelocity = 0;
                isGrounded = true;
            }
            else if (yVelocity < 0 && (hitbox.y - yVelocity) >= (obs.rect.y + obs.rect.height))
            {
                // Hitting head
                position.y = obs.rect.y + obs.rect.height - hitboxOffsetY;
                yVelocity = 0;
            }
            else
            {
                // Horizontal collision
                // Moving right into obstacle
                if (position.x + hitboxOffsetX < obs.rect.x && position.x + hitboxOffsetX + hitboxWidth > obs.rect.x)
                {
                    position.x = obs.rect.x - hitboxOffsetX - hitboxWidth;
                }
                // Moving left into obstacle
                else if (position.x + hitboxOffsetX > obs.rect.x && position.x + hitboxOffsetX < obs.rect.x + obs.rect.width)
                {
                    position.x = obs.rect.x + obs.rect.width - hitboxOffsetX;
                }
            }
        }
    }
}


void entity::Animate(int fps)
{
    if (animations.find(state) == animations.end()) return;

    Animation& anim = GetCurrentAnimation();
    frameRec.width = (float)anim.texture.width / anim.frameCount;
    frameRec.height = (float)anim.texture.height;

    frameCounter++;
    if (frameCounter >= (60 / fps))
    {
        frameCounter = 0;
        currentFrame++;
        if (currentFrame >= anim.frameCount) currentFrame = 0;
    }

    frameRec.x = (float)currentFrame * frameRec.width;
    frameRec.y = 0;
}

void entity::Draw(int heightOffset, int fontSize, Color color)
{
    Animation& anim = GetCurrentAnimation();

    // Draw entity name above hitbox
    DrawText(name, hitbox.x - textWidth / 2 + hitbox.width / 2, hitbox.y - heightOffset, fontSize, color);

    Rectangle sourceRec = frameRec;
    if (!facingRight) sourceRec.width *= -1;

    DrawTextureRec(anim.texture, sourceRec, position, WHITE);

     // Debug
     //DrawRectangleLines(hitbox.x, hitbox.y, hitbox.width, hitbox.height, RED); // Hitbox
     //DrawRectangleLines(position.x, position.y, frameRec.width, frameRec.height, WHITE); // Size of animated frame
     //DrawCircle(position.x, position.y, 3, GREEN);// Origin
}
    