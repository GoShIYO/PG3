#include "StageScene.h"
#include <Novice.h>
#include "NoviceInput.h"
#include <algorithm>
#include <cmath>

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

namespace
{
constexpr float kDeltaTime = 1.0f / 60.0f;
constexpr float kHpLerpSpeed = 5.0f;
}

void StageScene::Initialize()
{
	mPlayer = std::make_unique<Player>(640.0f, 560.0f, 10.0f, 100);
	mEnemys.resize(10);

	constexpr float startX = 100.0f;
	constexpr float startY = 100.0f;
	constexpr float distance = 24.0f;
	for (int i = 0; i < mEnemys.size(); i++)
	{
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(
			startX + i * distance, startY + i * distance * 1.5f, 12.0f, 100);
		mEnemys[i] = std::move(enemy);
	}
}

void StageScene::Update()
{
    mPlayer->Update();

    for (auto& enemy : mEnemys)
    {
        enemy->Update();
    }

    auto& playerBullets = mPlayer->mBullets;
    for (auto bulletIt = playerBullets.begin(); bulletIt != playerBullets.end();)
    {
        bool hitEnemy = false;
        for (auto& enemy : mEnemys)
        {
            if (enemy && enemy->hp > 0 && bulletIt->IsCollision(*enemy))
            {
                enemy->Damage(bulletIt->damage);
                hitEnemy = true;
                break;
            }
        }

        if (hitEnemy)
        {
            bulletIt = playerBullets.erase(bulletIt);
        }
        else
        {
            ++bulletIt;
        }
    }

    for (auto& enemy : mEnemys)
    {
        for (auto bulletIt = enemy->mBullets.begin(); bulletIt != enemy->mBullets.end();)
        {
            if (bulletIt->IsCollision(*mPlayer))
            {
                mPlayer->Damage(bulletIt->damage);
                bulletIt = enemy->mBullets.erase(bulletIt);
            }
            else
            {
                ++bulletIt;
            }
        }
    }

    mPlayer->UpdateHpDisplay(kDeltaTime, kHpLerpSpeed);
    for (auto& enemy : mEnemys)
    {
        enemy->UpdateHpDisplay(kDeltaTime, kHpLerpSpeed);
    }

    mEnemys.erase(
        std::remove_if(
            mEnemys.begin(), mEnemys.end(),
            [](const std::unique_ptr<Enemy>& enemy)
            {
                return enemy->hp <= 0;
            }),
        mEnemys.end());

    if (mEnemys.empty())
    {
        sSceneNo = CLEAR;
    }
}

void StageScene::Draw()
{
	mPlayer->Draw(0xFFCCCCFF);
	for (auto& enemy : mEnemys)
	{
		enemy->Draw(0xCCCCFFFF);
	}
    Novice::ScreenPrintf(0, 16, "Kill All Enemy!");
}

void StageScene::Object::Draw(uint32_t color)
{
    Novice::DrawEllipse(
        int(x), int(y),
        int(size), int(size),
        0.0f,
        color,
        kFillModeSolid
    );
}

void StageScene::Object::Damage(int damage)
{
    if (damage <= 0)
    {
        return;
    }
    hp -= damage;
    if (hp < 0)
    {
        hp = 0;
    }
}

void StageScene::Object::UpdateHpDisplay(float deltaTime, float lerpSpeed)
{
    if (maxHp <= 0)
    {
        return;
    }
    float target = static_cast<float>(hp);
    float t = lerpSpeed * deltaTime;
    if (t < 0.0f)
    {
        t = 0.0f;
    }
    else if (t > 1.0f)
    {
        t = 1.0f;
    }
    displayHp = std::lerp(displayHp, target, t);
}

void StageScene::Object::DrawHpBar(uint32_t backColor, uint32_t delayedColor, uint32_t currentColor, float widthMultiplier)const
{
    if (maxHp <= 0)
    {
        return;
    }

    const float barWidthF = size * widthMultiplier;
    int barWidth = static_cast<int>(barWidthF);
    if (barWidth < 1)
    {
        barWidth = 1;
    }
    const int barHeight = 6;
    const int left = static_cast<int>(x - barWidthF * 0.5f);
    const int top = static_cast<int>(y - size - 8.0f);

    Novice::DrawBox(left, top, barWidth, barHeight, 0.0f, backColor, kFillModeSolid);

    float delayedRatio = displayHp / static_cast<float>(maxHp);
    if (delayedRatio < 0.0f)
    {
        delayedRatio = 0.0f;
    }
    else if (delayedRatio > 1.0f)
    {
        delayedRatio = 1.0f;
    }
    int delayedWidth = static_cast<int>(barWidthF * delayedRatio);
    Novice::DrawBox(left, top, delayedWidth, barHeight, 0.0f, delayedColor, kFillModeSolid);

    float currentRatio = static_cast<float>(hp) / static_cast<float>(maxHp);
    if (currentRatio < 0.0f)
    {
        currentRatio = 0.0f;
    }
    else if (currentRatio > 1.0f)
    {
        currentRatio = 1.0f;
    }
    int currentWidth = static_cast<int>(barWidthF * currentRatio);
    Novice::DrawBox(left, top, currentWidth, barHeight, 0.0f, currentColor, kFillModeSolid);
}

bool StageScene::Bullet::Update()
{
	x += vx;
	y += vy;
	return x < 0 || x > 1280 || y < 0 || y > 720;
}

void StageScene::Player::Update()
{
    float moveX = 0.0f, moveY = 0.0f;
    if (NoviceInput::IsPressKey(DIK_LEFT)) moveX = -1;
    if (NoviceInput::IsPressKey(DIK_RIGHT)) moveX = 1;
    if (NoviceInput::IsPressKey(DIK_UP)) moveY = -1;
    if (NoviceInput::IsPressKey(DIK_DOWN)) moveY = 1;

    x += moveX * vx;
    y += moveY * vy;

    shootTimer += kDeltaTime;
    if (NoviceInput::IsPressKey(DIK_SPACE))
    {
        while (shootTimer >= kShootCooldown)
        {
            mBullets.emplace_back(x, y, damage);
            shootTimer -= kShootCooldown;
        }
    }
    else if (shootTimer > kShootCooldown)
    {
        shootTimer = kShootCooldown;
    }

    for (auto it = mBullets.begin(); it != mBullets.end();)
    {
        if (it->Update())
        {
            it = mBullets.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void StageScene::Player::Draw(uint32_t color)
{
    for (auto& bullet : mBullets)
    {
        bullet.Draw(0xE867A5FF);
    }
    Object::Draw(color);
    DrawHpBar(0x000000AA, 0xFF7043FF, 0x4CAF50FF, 4.0f);
}

void StageScene::Enemy::Update()
{
    x += vx;
    y += vy;
    if (x < 0 || x > 1280)
    {
        vx *= -1;
    }

    shootTimer += kDeltaTime;
    while (shootTimer >= kShootCooldown)
    {
        Bullet b(x, y, damage);
        b.vy = 5.0f;
        mBullets.emplace_back(std::move(b));
        shootTimer -= kShootCooldown;
    }

    for (auto it = mBullets.begin(); it != mBullets.end();)
    {
        if (it->Update())
        {
            it = mBullets.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void StageScene::Enemy::Draw(uint32_t color)
{
    for (auto& bullet : mBullets)
    {
        bullet.Draw(0xE867A5FF);
    }
    Object::Draw(color);
    DrawHpBar(0x000000AA, 0xFF7043FF, 0xFDD835FF, 2.5f);
}