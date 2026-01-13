#include "StageScene.h"

void StageScene::Initialize()
{
	mInputHandle = std::make_unique<InputHandle>();

	mInputHandle->AssignMoveLeftCommand2PressKeyA();
    mInputHandle->AssignMoveRightCommand2PressKeyD();

	mPlayer = std::make_unique<Player>();
	mPlayer->Init();
}

void StageScene::Update()
{
	mCommand = mInputHandle->HandleInput();

	if (mCommand)
	{
		mCommand->Execute(*mPlayer);
	}

	mPlayer->Update();
}

void StageScene::Draw()
{
	mPlayer->Draw();
}
