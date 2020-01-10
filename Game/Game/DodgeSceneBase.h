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
		this->nextScene = nextScene; //this �N���X���̂̃C���X�^���X�E�����o�ϐ��̑O�ɂ���
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