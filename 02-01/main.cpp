#include<iostream>
#include<format>
#include<string>
#include <typeinfo>

using namespace std;

template<typename T>
std::string FormatValue(T v)
{
	if constexpr (std::is_same_v<T, float>)
	{
		return std::format("{}f", v);
	}
	else
	{
		return std::format("{}", v);
	}
}

template<typename T>
T Min(T a, T b)
{
	return a < b ? a : b;
}

template<typename T>
void PrintMin(T a, T b)
{
	string result = format("Type: {} -> Min({}, {}) = {}\n",
		typeid(T).name(),
		FormatValue(a),
		FormatValue(b),
		FormatValue(Min(a, b))
	);

	cout << result << endl;
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