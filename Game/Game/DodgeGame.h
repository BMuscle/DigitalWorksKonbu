#pragma once
#include"DodgeSceneBase.h"
#include<Siv3D.hpp>

class DodgeGame :public DodgeSceneBase
{
public:
	DodgeGame(DODGE_SCENE* nextScene);
	~DodgeGame();
	void start(void);
	void update();
	void draw();
private:
	Audio* backAudio;
};