#include<iostream>

class Animal
{
public:
	Animal()
	{
		std::cout << "「動物」のコンストラクタ" << std::endl;
	}
    virtual ~Animal()
	{
		std::cout << "「動物」のデストラクタ" << std::endl;
	}

	virtual void Sound()
	{
		std::cout << "「動物」の声" << std::endl;
	}
};

class Cat : public Animal
{
public:
	Cat()
	{
		std::cout << "「猫」のコンストラクタ" << std::endl;
	}
	~Cat()
	{
		std::cout << "「猫」のデストラクタ" << std::endl;
	}

	void Sound() override
	{
		std::cout << "「猫」の声" << std::endl;
	}
};

class Dog : public Animal
{
public:
	Dog()
	{
		std::cout << "「犬」のコンストラクタ" << std::endl;
	}
	~Dog()
	{
		std::cout << "「犬」のデストラクタ" << std::endl;
	}

	void Sound() override
	{
		std::cout << "「犬」の声" << std::endl;
	}
};

int main()
{
	//動物のインスタンス作成
	Animal* animal = new Animal();
    animal->Sound();
    delete animal;
    std::cout << "--------------------" << std::endl;
	//ネコのインスタンス作成
	animal = new Cat();
    animal->Sound();
    delete animal;
	std::cout << "--------------------" << std::endl;
	//犬のインスタンス作成
    animal = new Dog();
    animal->Sound();
    delete animal;
	std::cout << "--------------------" << std::endl;

	return 0;
}