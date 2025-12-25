#pragma once
#include "SceneFWD.h"
#include <string>
#include <memory>

class GameManager
{
public:
	GameManager(const char* title,int windowWidth,int windowHeight);
	~GameManager() = default;

	int Run();

private:
	std::unique_ptr<IScene> mScenes[Scene::SCENE_COUNT];
	int mCurrentSceneNo;
	int mPrevSceneNo;

	std::string_view mSceneNames[Scene::SCENE_COUNT];
};

