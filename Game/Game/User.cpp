#include "User.h"

int User::user_id;
String User::user_name;

void User::initialize() {	//������

}
void User::finalize() {		//�I����

}

bool User::saveDataAccess(int id) {
	user_id = id;
}

bool User::createSaveData(int id, String name) {//���[�U�[�f�[�^�쐬
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	//----------���[�U�[�f�[�^�X�V-----------
	//SQL�o�C���h�p
	std::string sql = "UPDATE Users SET name = ?, play_start_date = date('now')"
		"WHERE id = ?;";

	//�X�e�[�g�����g�쐬
	sqlite3_prepare_v2(MySqlite3::getDB(),sql.c_str(), sql.size(), &stmt, &pzTest);
	//�X�e�[�g�n���h����U������
	sqlite3_reset(stmt);
	//�o�C���h
	sqlite3_bind_text(stmt, 1, name.narrow().c_str(), name.size(), SQLITE_TRANSIENT);//1�ڂ́H��name�ɂ���
	sqlite3_bind_int(stmt, 2, id);//2�ڂ́H��id�ɂ���
	sqlite3_step(stmt);//SQL���s
	sqlite3_finalize(stmt);//�X�e�[�g�����g����

	//�����Ń��[�U�[�f�[�^���擾������
	saveDataAccess(id);
	return true;
}

