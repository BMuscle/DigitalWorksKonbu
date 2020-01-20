#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "Mode.h"
#include "MiniGameBase.h"
#include "Soccer.h"
#include "ShoeKick.h"
#include "Dodge.h"
#include "MySocketServer.h"
#include "MyImageButton.h"
#include "GeneralSoundEffects.h"

class Game : public MyScene {
public:
	Game(MODE gamemode);
	~Game(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);
private:
	MiniGame* minigame;
	bool isStop;//�Q�[������~��Ԃ��ǂ���
	enum class POPUP {//�|�b�v�A�b�v�̏��
		RESTART,
		NEXTMAP,
		SIZE,
		NONE,
	};
	POPUP popUpState;//�|�b�v�A�b�v�̑I�����
	MyImageButton* popUpButton[(int)POPUP::SIZE];//���E�̖߂�{�^������{�^��
};