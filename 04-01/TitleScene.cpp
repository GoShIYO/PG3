#include "TitleScene.h"
#include "NoviceInput.h"
#include <Novice.h>

void TitleScene::Initialize()
{

}

void TitleScene::Update()
{
	if (NoviceInput::IsTriggerKey(DIK_RETURN))
	{
        sSceneNo = STAGE;
	}
}

void TitleScene::Draw()
{
	Novice::ScreenPrintf(0, 16, "Press Enter to Start");
}
