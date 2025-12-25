#pragma once
#include "IScene.h"
#include <vector>
#include <memory>

class StageScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	struct Object
	{
		float x = 0.0f, y = 0.0f;
		float vx = 0.0f, vy = 0.0f;
		float size = 0.0f;
		int hp = 0;
		int maxHp = 0;
		float displayHp = 0.0f;

		bool IsCollision(const Object& other)const
		{
			float dx = x - other.x;
			float dy = y - other.y;
			return dx * dx + dy * dy < (size + other.size) * (size + other.size);
		}
		void Damage(int damage);
		virtual void Draw(uint32_t color);
		void UpdateHpDisplay(float deltaTime, float lerpSpeed = 8.0f);
		void DrawHpBar(uint32_t backColor, uint32_t delayedColor, uint32_t currentColor, float widthMultiplier = 4.0f)const;
	};

	struct Bullet : Object
	{
		Bullet(float x_, float y_, int damage_) :
			damage(damage_)
		{
			x = x_;
			y = y_;
			vx = 0.0f;
			vy = -10.0f;
			size = 5.0f;
		}
		int damage;
		bool Update();
	};

	struct Player : Object
	{
		Player(float x_, float y_, float size_, int hp_)
		{
			x = x_;
			y = y_;
			size = size_;
			hp = hp_;
			maxHp = hp_;
			displayHp = static_cast<float>(hp_);
			vx = vy = 5.0f;
		}
		int damage = 20;
		std::vector<Bullet> mBullets;
		const float kShootCooldown = 0.5f;
		float shootTimer = kShootCooldown;
		void Update();
		void Draw(uint32_t color)override;
	};

	struct Enemy : Object
	{
		Enemy(float x_, float y_, float size_, int hp_)
		{
			x = x_;
			y = y_;
			size = size_;
			hp = hp_;
			maxHp = hp_;
			displayHp = static_cast<float>(hp_);
			vx = 4.0f;
			vy = 0.0f;
		}
		int damage = 10;
		const float kShootCooldown = 0.8f;
		float shootTimer = kShootCooldown;
		std::vector<Bullet> mBullets;
		void Update();
		void Draw(uint32_t color)override;
	};

	std::unique_ptr<Player> mPlayer;
	std::vector<std::unique_ptr<Enemy>> mEnemys;
};

