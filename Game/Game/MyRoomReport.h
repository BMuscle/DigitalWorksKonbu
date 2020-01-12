#pragma once
#include "MyRoom.h"
#include "MyKey.h"
#include "User.h"
#include <Siv3D.hpp>
#include "MyRoomSceneBase.h"
#include "TotalPlayTimeTimer.h"
#include "GeneralSoundEffects.h"

class MyRoomReport : public MyRoomSceneBase {
private:
	Audio* backAudio;//BGM
	int age;					//�Q�[�����N��
	String user_name;			//���[�U�[��
	float itemAcquisitionRate;	//�A�C�e���擾��
	int gameHighScore[(int)GAME_TYPE::SIZE];	//�Q�[�����n�C�X�R�A
	int gamePlayCount[(int)GAME_TYPE::SIZE];	//�Q�[�����v���C��
	String total_play_time;

	float alpha;

	int calcAge();//�N��v�Z
	void changeAlpha(void);//�A���t�@�l�ϓ�

public:
	MyRoomReport(MYROOM_SCENE* scenep);
	~MyRoomReport();
	bool isReady();
	void start();
	void update();
	void draw();
};