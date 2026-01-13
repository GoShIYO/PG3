#pragma once
#include "ICommand.h"

class InputHandle
{
public:
	ICommand* HandleInput();
	~InputHandle();
	void AssignMoveLeftCommand2PressKeyA();
    void AssignMoveRightCommand2PressKeyD();

private:
	ICommand* pPressKeyA = nullptr;
    ICommand* pPressKeyD = nullptr;
};

