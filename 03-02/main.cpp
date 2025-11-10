#include<iostream>
#include<typeinfo>
#include<format>

template<typename T>
class Math
{
public:
	T Min(T a, T b)
	{
		return a < b ? a : b;
	}
};

template<typename T>
void Print(T a, T b)
{
	if (typeid(T) != typeid(float))
		std::cout << std::format("Min({},{}) = ",a,b) << Math<T>().Min(a, b) << std::endl;
	else
		std::cout << std::format("Min({}f,{}f) = ", a, b) << Math<T>().Min(a, b) << 'f' << std::endl;
}

int main()
{
	Print<int>(1, 2);
    Print<double>(1.1, 2.2);
    Print<float>(12.1f, 12.11f);

	return 0;
}