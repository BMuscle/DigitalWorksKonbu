#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"

class MyRoom : public MyScene {
public:
	MyRoom(void);
	~MyRoom(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	Audio* backAudio;//BGM
	enum MODE {
		COLLECTION,	//collection�v�f���쐬����
		AVATAR,		//�A�o�^�[��ύX����
		NEXTMAP,	//�}�b�v�ֈړ�����
		EXIT,		//�Q�[�����I������
		SIZE,
	};
	
	String buttonName[SIZE];//�{�^���̃A�Z�b�g��
	MODE selectedMode;//����I������Ă��郂�[�h

	//�I������Ă��郂�[�h��ύX���邩��������
	void moveSelectMode();
	//�{�^���̕`��
	void drawButton();
};