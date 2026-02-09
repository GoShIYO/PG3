#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

using JudgeFn = void(*)(int, int);

void DelayReveal(JudgeFn fn, unsigned int delayMs, int roll, int userGuess)
{
	unsigned int ms = 0;
	while (ms <= delayMs)
	{
		int delay = delayMs / 3;
		Sleep(delay);
		printf(".");
		ms += delay;
	}
	printf("\n");
	fn(roll, userGuess);
}

int main()
{
	srand((unsigned int)time(NULL));

	printf("偶数か奇数か当ててみてください\n\n");
	while (true)
	{
		int roll = rand() % 6 + 1;
		printf("0(偶数)または1(奇数)を入力してください:");
		int input;
		scanf_s("%d", &input);
		if (input < 0 || input >1)
		{
			printf("0か1を入力してください\n");
			continue;
		}

		DelayReveal([](int roll, int userGuess)
			{
				if (roll % 2 == userGuess)
				{
					printf("正解\n");
				}
				else
				{
					printf("不正解\n");
				}
				printf("出目は %d でした\n", roll);
			}, 3000, roll, input);

		printf("--------------------------------------------------\n");
		printf("もう一度お試しですか？(y/n)\n");
		char endInput;
		scanf_s(" %c", &endInput, 1);

		if (endInput == 'y')
		{
			continue;
		}
		else if (endInput == 'n')
		{
			printf("終了\n");
			break;
		}
	}

	return 0;
}