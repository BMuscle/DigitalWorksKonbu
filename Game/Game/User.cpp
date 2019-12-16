#include "User.h"

int User::user_id;
String User::user_name;

void User::initialize() {	//������

}
void User::finalize() {		//�I����

}

bool User::simpleSaveDataAccess(int id, String& name, int64& total_play_time) {
	//��U������
	name = U"";
	total_play_time = 0;
	//�ϐ��錾
	int err;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT name, total_play_time FROM Users WHERE id = ?;";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	sqlite3_bind_int(stmt, 1, id);//1�ڂ́H��id�ɂ���
	if (err != SQLITE_OK) {
		//�G���[����
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			std::string str((char*)sqlite3_column_text(stmt, 0));//0��ځi���O��UTF-8�Ŏ󂯎��UTF32�ɕϊ�����)
			name = Unicode::FromUTF8(str);
			total_play_time = sqlite3_column_int64(stmt, 1);//1��� (�v���C���Ԃ̎擾)
		}
		if (err != SQLITE_DONE) {
			//�f�[�^���������擾�ł��Ȃ������ꍇ
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return true;
}

bool User::saveDataAccess(int id) {
	user_id = id;
	return false;
}

bool User::createSaveData(int id, String name) {//���[�U�[�f�[�^�쐬
	std::string ENname = name.toUTF8();//�G���R�[�h�ς݂̖��O UTF-32��UTF-8�ŕۑ�����
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	//----------���[�U�[�f�[�^�X�V-----------
	//SQL�o�C���h�p
	std::string sql = "UPDATE Users SET name = ?, play_start_date = date('now')"
		"WHERE id = ?;";

	//�X�e�[�g�����g�쐬
	sqlite3_prepare_v2(MySqlite3::getDB(),sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	//�X�e�[�g�n���h����U������
	sqlite3_reset(stmt);
	//�o�C���h
	sqlite3_bind_text(stmt, 1, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);//1�ڂ́H��name�ɂ���
	sqlite3_bind_int(stmt, 2, id);//2�ڂ́H��id�ɂ���
	sqlite3_step(stmt);//SQL���s
	sqlite3_finalize(stmt);//�X�e�[�g�����g����

	//�����Ń��[�U�[�f�[�^���擾������
	saveDataAccess(id);
	return true;
}

int User::getSaveDataSize() {//�󂫃Z�[�u�f�[�^��id�������Ɏ擾���閳�����0
	int id = 0;//�Ԃ�id�̏�����
	int err;//�G���[�R�[�h������
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	std::string sql = "SELECT COUNT(*) FROM Users WHERE name != '';";

	//�X�e�[�g�����g�쐬
	err = sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
	if (err != SQLITE_OK) {
		//�G���[����
	}
	else {
		//�f�[�^�̒��o
		while (SQLITE_ROW == (err = sqlite3_step(stmt))) {
			id = sqlite3_column_int(stmt, 0);//0��� id�̎擾
		}
		if (err != SQLITE_DONE) {
			//�f�[�^���������擾�ł��Ȃ������ꍇ
			id = 0;
		}
	}
	//�X�e�[�g�����g�̉��
	sqlite3_finalize(stmt);
	return id;
}