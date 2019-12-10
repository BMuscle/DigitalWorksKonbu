#pragma once
#include <Siv3D.hpp>

class User {
private:
	//�����o�ϐ�
	static int user_id;		//���[�U�[�ԍ�
	static String user_name;	//���[�U�[�l�[��
public:
	User() = delete;
	static void initialize();	//������
	static void finalize();		//�I����

	static bool saveDataAccess(int id);
	static bool createSaveData(int id, String name);

	//�Q�b�^�[�Z�b�^�[
	static int getUser_Id();
	static String getUser_Name();



};