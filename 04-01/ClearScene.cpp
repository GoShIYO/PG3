#include "ClearScene.h"
#include "NoviceInput.h"
#include <Novice.h>

void ClearScene::Initialize()
{

}

void ClearScene::Update()
{
	if (NoviceInput::IsTriggerKey(DIK_RETURN))
	{
		sSceneNo = TITLE;
	}
}

void ClearScene::Draw()
{
	Novice::ScreenPrintf(0, 16, "Press Enter return to Title");
}
