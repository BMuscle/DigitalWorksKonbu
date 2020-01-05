#pragma once
#include <Siv3D.hpp>
#include "MyKey.h"
#include "MyRoom.h"
#include "MyImageButton.h"
#include "MyRoomSceneBase.h"
#include "MySceneManager.h"


class MyRoomTitle : public MyRoomSceneBase {

public:
	MyRoomTitle(MYROOM_SCENE* scenep);
	~MyRoomTitle();

	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

private:
	Audio* backAudio;//BGM
	enum MODE {
		EXIT,		//�Q�[�����I������
		COLLECTION,	//collection�v�f���쐬����
		NEXTMAP,	//�}�b�v�ֈړ�����
		SIZE,
	};

	MyImageButton* button[SIZE];
	String buttonName[SIZE];	//�{�^���̃A�Z�b�g��
	MODE selectedMode;			//����I������Ă��郂�[�h

	//
	//�I������Ă��郂�[�h��ύX���邩��������
	void moveSelectMode();
	//�{�^���̕`��
	void drawButton();
};