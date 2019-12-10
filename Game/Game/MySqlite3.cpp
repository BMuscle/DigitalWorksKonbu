#include "MySqlite3.h"

sqlite3* MySqlite3::db;


bool MySqlite3::initialize() {	//������ DB�̏��������s��
	int err = sqlite3_open("savedata.db", &db);
	if (err != SQLITE_OK) {
		//�G���[����
		return false;//DB�̃I�[�v�����s
	}
	return true;//DB�̃I�[�v������
}
bool MySqlite3::finalize() {		//�I����
	int err = sqlite3_close(db);
	if (err != SQLITE_OK) {
		//�G���[����
		return false;	//DB�̃N���[�Y���s
	}
	return true;//DB�̃N���[�Y����
}
bool MySqlite3::DBCREATE() {		//��{�g�p���Ȃ��@�f�[�^�x�[�X�̏����ݒ���s���B DB�t�@�C�������Ă�����s
	char* errMsg = NULL;
	int err = 0;

	err = sqlite3_exec(db,
		"CREATE TABLE IF NOT EXISTS myTable "
		"(id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name CHAR(32) NOT NULL)",
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}
const sqlite3* MySqlite3::getDB() {//�f�[�^�x�[�X�ւ̃|�C���^���Q�Ƃ���
	return db;
}