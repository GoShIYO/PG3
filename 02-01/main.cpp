#include<iostream>
#include<format>
#include<string>
#include <typeinfo>

using namespace std;

template<typename T>
T Min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
void PrintMin(T a, T b)
{
	const char* type = typeid(T).name();
	string result = std::format("Type: {} -> Min({}, {}) = {}\n", type, a, b, Min(a, b));

	std::cout << result << std::endl;
}

int main()
{
	int intA = 2, intB = 5;
	float floatA = 0.9999999f, floatB = 1.0f;
	double doubleA = 7.5, doubleB = 7.55;

	PrintMin(intA, intB);

	PrintMin(floatA, floatB);

	PrintMin(doubleA, doubleB);

	return 0;
}