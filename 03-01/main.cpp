#include<iostream>

class Enemy
{
public:
    
    void Approach()
    {
        std::cout << "接近" << std::endl;
    }
    void Shoot()
    {
        std::cout << "射撃" << std::endl;
    }
    void Leave()
    {
        std::cout << "離脱" << std::endl;
    }
    static void(Enemy::* ActionTable[])();
};

void(Enemy::* Enemy::ActionTable[])() =
{
    &Enemy::Approach,
    &Enemy::Shoot,
    &Enemy::Leave
};

void Update(Enemy& enemy, int index)
{
    (enemy.*Enemy::ActionTable[index])();
}

int main()
{
    Enemy enemy;
    for (int i = 0; i < 3; i++)
    {
        Update(enemy, i);
    }
        
    return 0;
}