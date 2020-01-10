#pragma once
#include<Siv3D.hpp>
#include"DodgeSceneBase.h"
#include"MyKey.h"
#include"Dodge.h"
#include"MySceneManager.h"

class DodgeTitle:public DodgeSceneBase{
public:	
	DodgeTitle(DODGE_SCENE* nextScene);
	~DodgeTitle();
	 void start(void);
	 void update();
	 void draw();
private:
	Audio *backAudio;
	enum MODE{
		MAP,
		GAME,
	};
	MODE nowselect = GAME;
};
