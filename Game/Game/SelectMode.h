#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "Mode.h"

class SelectMode : public MyScene {
public:
	SelectMode(void);
	~SelectMode(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

	MODE getSelectedMode();//�I������Ă��郂�[�h��Ԃ��B�V�[���ڍs���Ɏ󂯓n��
private:
	Audio* backAudio;
	MODE selectedMode;//���ݑI������Ă��郂�[�h
};
