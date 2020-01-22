#pragma once
#include<Siv3D.hpp>
#include"DodgeSceneBase.h"
#include"MyKey.h"
#include"Dodge.h"
#include"MySceneManager.h"

class DodgeResult :public DodgeSceneBase {
public:
	DodgeResult(DODGE_SCENE* nextScene);
	~DodgeResult();
	void start(void);
	void update();
	void draw();
private:
	Audio* backAudio;
	enum MODE {
		MAP,
		TITLE,
	};
	MODE nowselect = MAP;
};
