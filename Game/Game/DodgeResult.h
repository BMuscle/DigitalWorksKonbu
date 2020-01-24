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
	DodgeResult(DODGE_SCENE* nextScene);//3�񕪂̃X�s�[�h�A�������A�q�b�g������󂯎��I�I
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
	//�摜�̃{�^��
	MyImageButton* button[SIZE];

	float dVelocity[DODGE_GAME_PLAY_COUNT];//�����x
	int hitLevel[DODGE_GAME_PLAY_COUNT];//������
	bool hit[DODGE_GAME_PLAY_COUNT];//�����������ǂ���
};
