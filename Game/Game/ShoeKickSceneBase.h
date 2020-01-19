#pragma once

enum class SHOEKICK_SCENE {
	TITLE,
	GAME,
	RESULT,
	NONE,
};


class ShoeKickSceneBase {
private:
	SHOEKICK_SCENE* nextSceneP;
public:
	ShoeKickSceneBase(SHOEKICK_SCENE* scenep) {
		nextSceneP = scenep;
	}
	virtual ~ShoeKickSceneBase() {
	}
	void setNextScene(SHOEKICK_SCENE scene) {
		*nextSceneP = scene;
	}
	virtual bool isReady() = 0;
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
