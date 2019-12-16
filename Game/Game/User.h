#pragma once
#include <Siv3D.hpp>
#include "MySqlite3.h"
#include "sqlite3.h"

class User {
private:
	//�����o�ϐ�
	static int user_id;	//���[�U�[�ԍ�	
	static String user_name;	//���[�U�[�l�[��
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



};