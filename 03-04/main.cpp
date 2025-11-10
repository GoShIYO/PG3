#include<iostream>
#include<numbers>

struct CircleSize
{
	float radius;
};

struct RectangleSize
{
	float width;
	float height;
};

template<typename SizeType>
class IShape
{
public:
	IShape(const SizeType& size) : size(size), area(0) {}
	virtual ~IShape() = default;
	virtual void Size() = 0;
	virtual void Draw() = 0;
protected:
	SizeType size;
	float area;
};

class Circle : public IShape<CircleSize>
{
public:
	Circle(const CircleSize& size) : IShape(size) {}
	void Size() override
	{
		area = std::numbers::pi_v<float> *size.radius * size.radius;
	}
	void Draw() override
	{
		std::cout << "円の面積は" << area << std::endl;
	}
};

class Rectangle : public IShape<RectangleSize>
{
public:
	Rectangle(const RectangleSize& size) : IShape(size) {}
	void Size() override
	{
		area = size.width * size.height;
	}
	void Draw() override
	{
		std::cout << "矩形の面積は" << area << std::endl;
	}
};

bool PrintShape(int choice)
{
	switch (choice)
	{
	case 1:
	{
		CircleSize size;
		std::cout << "半径を入力してください:";
		std::cin >> size.radius;
		Circle circle(size);
		circle.Size();
		circle.Draw();
	}
	break;
	case 2:
	{
		RectangleSize size;
		std::cout << "幅と高さを入力してください:";
		std::cin >> size.width >> size.height;
		Rectangle rectangle(size);
		rectangle.Size();
		rectangle.Draw();
	}
	break;
	default:
		std::cout << "無効な入力です" << std::endl;
		break;
	}
	std::cout << "もう一回やりますか y / n ? :";
	char input;
	std::cin >> input;
	if (input == 'y')return true;
	else if (input == 'n')return false;
	return true;
}

int main()
{
	int choice;

	do
	{
		std::cout << "1. 円 2. 矩形" << std::endl;
		std::cin >> choice;
		std::cout << std::endl;

	} while (PrintShape(choice));

	return 0;
}