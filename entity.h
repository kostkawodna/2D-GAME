#pragma once
#include "raylib.h"
#include <map>
#include <string>
#include <vector>
#include "level.h"

struct Animation
{
    Texture2D texture;
    int frameCount;
};

class entity
{
public:
    entity();
    virtual ~entity();

    // Hitbox
    float hitboxOffsetX = 0;
    float hitboxOffsetY = 0;
    float hitboxWidth = 0;
    float hitboxHeight = 0;
    Rectangle hitbox;

    Vector2 position = { 0, 0 };
    Vector2 GetActualPosition() const
    {
        return { position.x + hitboxOffsetX + hitboxWidth / 2,
                 position.y + hitboxOffsetY + hitboxHeight };
    }

    // Physics
    float yVelocity = 0.0f;
    float gravity = 0.5f;
    bool isGrounded = false;

    // Animation
    Rectangle frameRec;
    std::map<std::string, Animation> animations;
    std::string state;
    int currentFrame = 0;
    int frameCounter = 0;
    bool facingRight = true;

    // Drawing
    const char* name = "Entity";
    int textWidth = 0;

    // Functions
    virtual void Update(const std::vector<Obstacle>& obstacles) = 0;
    void Draw(int heightOffset = 0, int fontSize = 10, Color color = PINK);
    void AddAnimation(const std::string& stateName, const std::string& filePath, int frames);
    void SetState(const std::string& newState);

protected:
    Animation& GetCurrentAnimation();
    void HandleCollisions(const std::vector<Obstacle>& obstacles);
    void Animate(int fps = 12);
};
