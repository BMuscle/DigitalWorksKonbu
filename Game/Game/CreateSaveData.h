#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "MySqlite3.h"
#include "MyImageButton.h"
#include "TotalPlayTimeTimer.h"
#include "CreateSaveData.h"

class CreateSaveData : public MyScene {
public:
	CreateSaveData(int user_id);
	~CreateSaveData(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

private:
	Audio* backAudio;//BGM
	bool isStart;//���[�h���I����Ă��邩�ǂ����̃t���O
	int createUser_Id;//���[�U�[���쐬����Ώ�ID

	Font nameFont;//���O���͗��p�t�H���g
	TextBox namebox;//���O���͗�
	enum class BUTTON {
		RETURN,
		DECISION,
		SIZE,
	};

	enum class SELECT_STATE {
		RETURN,
		TEXT,
		DECISION,
		POPUP,
	};
	SELECT_STATE selectState;
	MyImageButton* button[(int)BUTTON::SIZE];//���E�̖߂�{�^������{�^��

	enum class POPUP {//�|�b�v�A�b�v�̏��
		DECISION,
		RETURN,
		SIZE,
		NONE,
	};
	POPUP popUpState;//�|�b�v�A�b�v�̑I�����
	MyImageButton* popUpButton[(int)POPUP::SIZE];//���E�̖߂�{�^������{�^��
	void selectUpdate();//���݂̈ړ���ԂɑΉ�����v�Z����
	void selectMove();//�I����Ԃ̈ړ��`�F�b�N���ړ�����

	void popUpUpdate();//�|�b�v�A�b�v�̌v�Z����
	void popUpMove();//�|�b�v�A�b�v�̈ړ��`�F�b�N�ړ�����
	void popUpDraw();//�|�b�v�A�b�v�̕`��

	void createData();//�Z�[�u�f�[�^�����ۂɍ쐬
	
};