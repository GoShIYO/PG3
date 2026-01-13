#include <iostream>
#include <thread>

int main()
{
	int num = 0;

	std::thread th1([&]
		{
			std::cout << "thread " << num++ << std::endl;
		});
	th1.join();

	std::thread th2([&]
		{
			std::cout << "thread " << num++ << std::endl;
		});
	th2.join();

	std::thread th3([&]
		{
			std::cout << "thread " << num++ << std::endl;
		});
	th3.join();

	return 0;
}