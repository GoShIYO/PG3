#pragma once

enum Scene
{
	TITLE,
	STAGE,
	CLEAR,

	SCENE_COUNT,
};

class IScene
{
protected:
	static inline int sSceneNo = TITLE;

public:
	virtual ~IScene() = default;

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	int GetSceneNo() { return sSceneNo; }

};

