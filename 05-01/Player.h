#pragma once
#include "math/Vector2.h"
class Player
{
public:
	void Init();
	void Update();
	void Draw();

	void MoveLeft();
    void MoveRight();

private:
	KamataEngine::Vector2 mPosition;
    KamataEngine::Vector2 mVelocity;
	const float kSpeed = 5.0f;
	const float kSize = 20.0f ;
};

