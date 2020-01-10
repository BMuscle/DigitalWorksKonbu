#pragma once

enum class DODGE_SCENE {
	TITLE,
	GAME,
	RESULT,
	SIZE,
};

class DodgeSceneBase{
public:
	DodgeSceneBase(DODGE_SCENE* nextScene) {
		this->nextScene = nextScene; //this クラス自体のインスタンス・メンバ変数の前につける
	}
	virtual ~DodgeSceneBase() {}
	virtual void update() = 0;
	virtual void draw() = 0;
	void setNextScene(DODGE_SCENE scene) {
		*nextScene = scene;
	}
	
private:
	DODGE_SCENE* nextScene;
};