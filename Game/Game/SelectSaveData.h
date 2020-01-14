#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "MySqlite3.h"
#include "MyImageButton.h"
#include "TotalPlayTimeTimer.h"
#include "GeneralSoundEffects.h"

constexpr int USER_SIZE = 3;//���[�U�̍ő吔 3

class SelectSaveData : public MyScene {
public:
	SelectSaveData(void);
	~SelectSaveData(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

	int getSelectUser_Id();
private:
	Audio* backAudio;//BGM
	struct Frame{				//�Z�[�u�f�[�^�̃t���[���摜
		int id;					//DB�̃��[�U�[�\�̎�L�[
		String user_name;		//���[�U�[�̖��O
		String total_play_time;	//���v���C����
		int x;					//�`����WX
		int y;					//�`����WY
	};
	int frameCount;				//�t���[�������J�E���g����
	bool selectDeleteButton;	//�폜�{�^����I�����Ă��邩�ǂ���
	bool isPopUp;				//�|�b�v�A�b�v�\����Ԃ��ǂ���
	enum POPUP {
		RETURN,
		DECISION,
		SIZE,
		NONE,
	};
	POPUP popUpState;
	MyImageButton* popUpButton[(int)POPUP::SIZE];//���E�̖߂�{�^������{�^��

	Frame user_frame[USER_SIZE];//�Z�[�u�f�[�^�̃t���[���摜�R��
	int selectedUser;			//���ݑI������Ă��郆�[�U�[(�ォ��0,1,2)
	int selectCountPrev;		//�I�����ꂽ���̃t���[����

	//�t���[�������J�E���g�A�b�v����
	void updateFrameCount();
	//���[�U�[�̑I����Ԃ��X�V����(true = ����� false = ������)
	void rotateSelectedUser(bool isUp = true);
	//�Z�[�u�f�[�^���폜���A���݂̕\�������Z�b�g����
	void deleteSaveData();
};

