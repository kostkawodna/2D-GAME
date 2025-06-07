#pragma once
#include <raylib.h>
#include <string>
#include <map>

enum class AnimationState
{
	IDLE,
	WALK,
	RUN,
	JUMP
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

	void LoadPlayerTexture();
	void DrawPlayer();
	void UpdatePlayer();

private:
	std::map<AnimationState, Animation> animations;
	Texture2D texture;
	Rectangle frameRec;
	AnimationState state = AnimationState::IDLE;
	Animation& GetCurrentAnimation();

	int currentFrame = 0;
	int frameCounter = 0;
	bool facingRight = true;
	bool isJumping = false;
};