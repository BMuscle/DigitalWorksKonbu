#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "MySqlite3.h"

class CreateSaveData : public MyScene {
public:
	CreateSaveData(void);
	~CreateSaveData(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

private:
	Audio* backAudio;//BGM
	bool isStart;//���[�h���I����Ă��邩�ǂ����̃t���O

	Font nameFont;//���O���͗��p�t�H���g
	TextBox namebox;//���O���͗�

	enum class POPUP_STATE {//�|�b�v�A�b�v�̏��
		YES,
		NO,
	};
	POPUP_STATE popUpState;//�|�b�v�A�b�v�̑I�����
	void popUpDraw();//�|�b�v�A�b�v�̕`��
};