#include "Player.h"
#include "Novice.h"

void Player::Init()
{
	mPosition = { 100,100 };
	mVelocity = { 0,0 };
}

void Player::Update()
{
	mPosition.x += mVelocity.x;
    mPosition.y += mVelocity.y;
	
	mVelocity = { 0,0 };
}

void Player::Draw()
{
	Novice::DrawBox(int(mPosition.x - kSize * 0.5f),int(mPosition.y - kSize * 0.5f),int(kSize),int(kSize),0,WHITE,kFillModeSolid);
}

void Player::MoveLeft()
{
	mVelocity.x = -kSpeed;
}

void Player::MoveRight()
{
	mVelocity.x = kSpeed;
}