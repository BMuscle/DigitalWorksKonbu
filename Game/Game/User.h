#pragma once
#include <Siv3D.hpp>
#include "MySqlite3.h"
#include "sqlite3.h"

class User {
private:
	//�����o�ϐ�
	static int user_id;		//���[�U�[�ԍ�
	static String user_name;	//���[�U�[�l�[��
public:
	User() = delete;
	static void initialize();	//������
	static void finalize();		//�I����

	static bool simpleSaveDataAccess(int id, String& name, int& total_play_time);//�ȒP�ȃ��[�U�[�f�[�^�ւ̃A�N�Z�X�A�g�p�ړI�͑I������Ƃ��̊ȈՕ\���p
	static bool saveDataAccess(int id);//���[�U�[�f�[�^�̑I�� ���N���X�̕ϐ��ɕۑ�����
	static bool createSaveData(int id, String name);//���[�U�[�f�[�^�̍쐬

	static int detectionSaveData();//�󂫃Z�[�u�f�[�^��id�������Ɏ擾���閳�����0

	//�Q�b�^�[�Z�b�^�[
	static int getUser_Id();
	static String getUser_Name();



};