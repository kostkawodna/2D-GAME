#pragma once
#include <raylib.h>
#include <string>
#include <map>
#include <vector>
#include "level.h"

enum class AnimationState
{
	IDLE,
	WALK,
	RUN,
	JUMP,
	ATTACK1,
	DEFEND
};

struct Animation
{
	Texture2D texture;
	int frameCount;
};

class player
{
public:
	int Health;
	Vector2 playerPos = { 0, 0 };
	Vector2 playerSpeed = { 3, 3 };

	Rectangle frameRec; // used for camera and animation

	void DrawPlayer();
	void UpdatePlayer(const std::vector<Obstacle>& obstacles);
	void LoadPlayerTexture();

private:
	// Player texture
	std::map<AnimationState, Animation> animations;
	Texture2D texture;
	AnimationState state = AnimationState::IDLE;
	Animation& GetCurrentAnimation();

	// Player HitBox
	float hitboxOffsetX = 32.0f;
	float hitboxOffsetY = 27.0f;
	float hitboxWidth = 32.0f;
	float hitboxHeight = 35.0f;
	Rectangle playerHitBox;

	// Username
	const char* playerName = "jj_joker";
	int textWidth = MeasureText(playerName, 10);

	// Animation
	int currentFrame = 0;
	int frameCounter = 0;

	// Physics and movement
	void HandleCollisions(const std::vector<Obstacle>& obstacles);
	bool facingRight = true;
	bool isGrounded = false;
    bool isAttacking = false;
	bool isDefending = false;

	float yVelocity = 0.0f;
	float gravity = 0.5f;
	float walkSpeed = 2.0f;
	float runSpeed = 4.0f;
};