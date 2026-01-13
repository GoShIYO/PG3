#include "InputHandle.h"
#include "NoviceInput.h"

ICommand* InputHandle::HandleInput()
{
	if (NoviceInput::IsPressKey(DIK_D))return pPressKeyD;
	else if (NoviceInput::IsPressKey(DIK_A))return pPressKeyA;
	
	return nullptr;
}

InputHandle::~InputHandle()
{
	delete pPressKeyA;
    delete pPressKeyD;
}

void InputHandle::AssignMoveLeftCommand2PressKeyA()
{
	ICommand* command = new MoveLeftCommand();
	pPressKeyA = command;
}

void InputHandle::AssignMoveRightCommand2PressKeyD()
{
	ICommand* command = new MoveRightCommand();
	pPressKeyD = command;
}
