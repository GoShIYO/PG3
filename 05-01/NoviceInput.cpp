#include "NoviceInput.h"
#include <Novice.h>

char NoviceInput::keys[256] = { 0 };
char NoviceInput::prevKeys[256] = { 0 };

void NoviceInput::Run()
{
	// キー入力を受け取る
	memcpy(prevKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
}

bool NoviceInput::IsPressKey(int key)
{
	return keys[key];
}

bool NoviceInput::IsTriggerKey(int key)
{
	return keys[key] && !prevKeys[key];
}

bool NoviceInput::IsReleaseKey(int key)
{
	return !keys[key] && prevKeys[key];
}
