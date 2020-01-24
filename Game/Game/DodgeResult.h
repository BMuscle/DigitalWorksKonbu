#pragma once
#include<Siv3D.hpp>
#include"DodgeSceneBase.h"
#include"MyKey.h"
#include"Dodge.h"
#include"MySceneManager.h"
#include "MyImageButton.h"
#include "GeneralSoundEffects.h"
constexpr int DODGE_GAME_PLAY_COUNT = 3;

class DodgeResult :public DodgeSceneBase {
public:
	DodgeResult(DODGE_SCENE* nextScene);//3回分のスピード、命中率、ヒット判定を受け取る！！
	~DodgeResult();
	void start(void);
	void update();
	void draw();
private:
	Audio* backAudio;
	enum MODE {
		MAP,
		TITLE,
		SIZE,
	};
	MODE nowselect = MAP;

	Font mainFont;
	Font subFont;
	//画像のボタン
	MyImageButton* button[SIZE];

	float dVelocity[DODGE_GAME_PLAY_COUNT];//加速度
	int hitLevel[DODGE_GAME_PLAY_COUNT];//命中率
	bool hit[DODGE_GAME_PLAY_COUNT];//当たったかどうか
};
