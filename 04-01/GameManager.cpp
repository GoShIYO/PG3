#include "GameManager.h"
#include <Novice.h>
#include "NoviceInput.h"

GameManager::GameManager(const char* title, int windowWidth, int windowHeight)
	:mCurrentSceneNo(TITLE), mPrevSceneNo(0)
{
	mScenes[TITLE] = std::make_unique<TitleScene>();
	mScenes[STAGE] = std::make_unique<StageScene>();
	mScenes[CLEAR] = std::make_unique<ClearScene>();

	mSceneNames[TITLE] = "TitleScene";
    mSceneNames[STAGE] = "StageScene";
    mSceneNames[CLEAR] = "ClearScene";

	// ライブラリの初期化
	Novice::Initialize(title, windowWidth, windowHeight);
}

int GameManager::Run()
{
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();
		NoviceInput::Run();

		mPrevSceneNo = mCurrentSceneNo;
		mCurrentSceneNo = mScenes[mCurrentSceneNo]->GetSceneNo();

		if (mPrevSceneNo != mCurrentSceneNo)
		{
			mScenes[mCurrentSceneNo]->Initialize();
		}
		///
		/// ↓更新処理ここから
		///
		mScenes[mCurrentSceneNo]->Update();
		///	
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		mScenes[mCurrentSceneNo]->Draw();

		Novice::ScreenPrintf(0, 0, "Scene:%s", mSceneNames[mCurrentSceneNo].data());
		
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (NoviceInput::IsTriggerKey(DIK_ESCAPE))
		{
			break;
		}
	}
	// ライブラリの終了
	Novice::Finalize();

	return 0;
}
