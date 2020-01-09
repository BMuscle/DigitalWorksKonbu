#pragma once
#include <Siv3D.hpp>
#include "MySqlite3.h"
#include "sqlite3.h"
#include <map>
#include <vector>
#include <random>
#include "TotalPlayTimeTimer.h"

enum class GAME_TYPE {//�f�[�^�x�[�X�ɓ����Ă�l�́{�P
	SOCCER = 0,
	SHOEKICK = 1,
	DODGE = 2,
	SIZE = 3,
};

class User {
private:
	//�����o�ϐ�
	static int user_id;						//���[�U�[�ԍ�	
	static String user_name;				//���[�U�[�l�[��
	static int user_point;					//���݂̏����|�C���g
	static int64 user_total_play_time;		//���v���C����[s]
	static String user_play_start_date;		//�v���C�J�n��




	static std::map<int, bool> Items[(int)GAME_TYPE::SIZE];//���[�U�[�������Ă���A�C�e���ꗗ

	static bool selectUser(int id);//���[�U�[�̃f�[�^��ϐ��Ɋi�[����
	static bool selectUserItems(int id);//���[�U�[�A�C�e���f�[�^��ϐ��Ɋi�[����
	//�A�C�e��ID���擾
	static int getItemId(int game_id, int key);

	static String getItemName(int game_id, int key);
	//���[�U�̃A�C�e�����X�V����(flag���P��)
	static void setUserItem(int game_id, int key);

	

public:
	User() = delete;
	//������
	static void initialize();	
	//�I����
	static void finalize();		
	//�ȒP�ȃ��[�U�[�f�[�^�ւ̃A�N�Z�X�A�g�p�ړI�͑I������Ƃ��̊ȈՕ\���p
	static bool simpleSaveDataAccess(int id, String& name, int64& total_play_time);
	//���[�U�[�f�[�^�̑I�� ���N���X�̕ϐ��ɕۑ�����
	static bool saveDataAccess(int id);
	//���[�U�[�f�[�^�̍쐬
	static bool createSaveData(int id, String name);
	//�Z�[�u�f�[�^�̑��݂��鐔��Ԃ�
	static int getSaveDataSize();

	//�Q�b�^�[�Z�b�^�[

	//���[�UID�̎擾
	static int getUser_Id();
	//���[�U�[�l�[���̎擾
	static String getUser_Name();
	//���[�U�[���A�C�e���������Ă��邩�ǂ���true false�ŕԂ� key��csv�̈�ԍ��̗�
	static bool getHasItems(GAME_TYPE type, int key);

	//�K�`���p �擾�ł���A�C�e�������݂��邩�ǂ���
	static bool hasAllItem();

	//�K�`�������ĂP�A�C�e�����擾���� �擾�ł������^�U�l�ŕԂ�
	static bool getRandomGacha(String& itemName, int& key, GAME_TYPE& type);

	//�|�C���g�̉��Z
	static bool addUserPoint(int addPoint);
	//�|�C���g�̌��Z
	static bool subUserPoint(int subPoint);
	//�|�C���g�̎擾
	static int getUserPoint();
	
	//�v���C���Ԃ��X�V����
	static bool setTotalPlayTime();
	
	//�Q�[���X�R�A��o�^���� 0 ~ 100�͈̔͂�
	static bool addGameScore(GAME_TYPE type, int score);

	//�Q�[���̃n�C�X�R�A���擾����
	static int getGameHighScore(GAME_TYPE type);

	//�Q�[���̃v���C�񐔂��擾����
	static int getGamePlayCount(GAME_TYPE type);

	//�A�C�e���擾�����擾����
	static float getItemAcquisitionRate();

	//�v���C���ԕԂ� �Z���Z��
	static String getTotalPlayTime();

};