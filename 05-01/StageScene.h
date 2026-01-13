#pragma once
#include "IScene.h"
#include "ICommand.h"
#include "InputHandle.h"
#include "Player.h"
#include <memory>

class StageScene : public IScene
{
public:
	void Initialize() override;
	void Update() override;
	void Draw() override;
private:
	ICommand* mCommand = nullptr;
	std::unique_ptr<InputHandle> mInputHandle = nullptr;
	std::unique_ptr<Player> mPlayer = nullptr;
};

