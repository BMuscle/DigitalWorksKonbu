#pragma once
#include<Siv3D.hpp>
#include "MyScene.h"
#include "MyKey.h"
#include "MySceneManager.h"
#include "User.h"
#include "MySqlite3.h"

constexpr int USER_SIZE = 3;//���[�U�̍ő吔 3

class SelectSaveData : public MyScene {
public:
	SelectSaveData(void);
	~SelectSaveData(void);
	bool isReady(void);
	void start(void);
	void update(void);
	void draw(void);

	
private:
	Audio* backAudio;//BGM
	struct Frame{//�Z�[�u�f�[�^�̃t���[���摜
		int id;	//DB�̃��[�U�[�\�̎�L�[
		String user_name;//���[�U�[�̖��O
		int x;	//�`����WX
		int y;	//�`����WY
	};
	int frameCount;//�t���[�������J�E���g����
	Frame user_frame[USER_SIZE];//�Z�[�u�f�[�^�̃t���[���摜�R��
	int selectedUser;		//���ݑI������Ă��郆�[�U�[
	int selectCountPrev;	//�I�����ꂽ���̃t���[����

	void updateFrameCount();
	void rotateSelectedUser(bool isUp = true);
};

