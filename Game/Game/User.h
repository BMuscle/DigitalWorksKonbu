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

	static bool saveDataAccess(int id);//���[�U�[�f�[�^�̑I��
	static bool createSaveData(int id, String name);//���[�U�[�f�[�^�̍쐬

	//�Q�b�^�[�Z�b�^�[
	static int getUser_Id();
	static String getUser_Name();



};