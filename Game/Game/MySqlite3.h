#pragma once
#include "sqlite3.h"

class MySqlite3 {
private:
	static sqlite3* db;//�f�[�^�x�[�X�ւ̃|�C���^
public:
	MySqlite3() = delete;
	static bool initialize();	//������ DB�̏��������s��
	static bool finalize();		//�I����
	static bool DBCREATE();		//��{�g�p���Ȃ��@�f�[�^�x�[�X�̏����ݒ���s���B DB�t�@�C�������Ă�����s
	static sqlite3* getDB();//�f�[�^�x�[�X�ւ̃|�C���^���Q�Ƃ���

};