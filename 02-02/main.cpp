#include<iostream>

constexpr int hourly_wage = 1226;
constexpr int recursion_wage_base = 100;

// 通常賃金
int CacuDefaultSalary(int hours)
{
	return hours * hourly_wage;
}

// n時間目の賃金
int GetHourlyRecursionWage(int hour)
{
	if (hour == 1)
		return recursion_wage_base;
	else
		return (GetHourlyRecursionWage(hour - 1) * 2) - 50;
}
// n時間目の総賃金
int CacuRecursionSalary(int hours)
{
	if (hours <= 0)
		return 0;
	return GetHourlyRecursionWage(hours) + CacuRecursionSalary(hours - 1);
}

int main()
{
	int hour = 0;
	int dafault_salary = 0;
	int recursion_salary = 0;
	while (dafault_salary >= recursion_salary)
	{
		hour++;
        dafault_salary = CacuDefaultSalary(hour);
        recursion_salary = CacuRecursionSalary(hour);

		printf("%d 時間\n通常賃金 %d\n再帰賃金 %d\n", hour, dafault_salary, recursion_salary);
		printf("------------------------------\n");
	}
	printf("%d 時間目に再帰的賃金体系の方が儲かる\n", hour);

	return 0;
}