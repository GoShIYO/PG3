#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class NoviceInput
{
public:
	static void Run();

	static bool IsPressKey(int key);
	static bool IsTriggerKey(int key);
	static bool IsReleaseKey(int key);

private:
	static char keys[256];
	static char prevKeys[256];
};

