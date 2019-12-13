#include "MySqlite3.h"

sqlite3* MySqlite3::db;

/* SQL���s
//-------------------------
err = sqlite3_exec(db,
	,
	NULL, NULL, &errMsg);

if (err != SQLITE_OK) {
	sqlite3_free(errMsg);
	return false;
}
*/
bool MySqlite3::initialize() {	//������ DB�̏��������s��
	int err = sqlite3_open("savedata.db", &db);
	if (err != SQLITE_OK) {
		//�G���[����
		return false;//DB�̃I�[�v�����s
	}

	char* errMsg = NULL;
	err = 0;

	err = sqlite3_exec(db,
		"PRAGMA foreign_keys = true;",
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
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
	//-------���[�U�[�쐬---------
	err = sqlite3_exec(db,
		"CREATE TABLE Users("
		"id integer primary key,"
		"name text,"
		"point integer default 0,"
		"total_play_time integer,"
		"play_start_date text"
		");",
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	//-------�A�C�e���쐬-------------
	err = sqlite3_exec(db,
		"CREATE TABLE Items("
		"id integer primary key,"
		"name text"
		");",
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	//--------�R���N�V�����쐬----------
	err = sqlite3_exec(db,
		"CREATE TABLE Collections("
		"id integer primary key,"
		"name text"
		");",
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	//-------���[�U�[�A�C�e���쐬------
	err = sqlite3_exec(db,
		"CREATE TABLE UserItems("
		"id integer primary key autoincrement,"
		"user_id integer,"
		"item_id integer,"
		"flag default 0 check(flag < 2 and flag > -1),"
		"foreign key (user_id) references Users(id),"
		"foreign key (item_id) references Items(id)"
		");",
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	//----------���[�U�[�R���N�V�����쐬---------
	err = sqlite3_exec(db,
		"CREATE TABLE UserCollections("
		"id integer primary key autoincrement,"
		"user_id integer,"
		"collection_id integer,"
		"flag default 0 check(flag < 2 and flag > -1),"
		"foreign key (user_id) references Users(id),"
		"foreign key (collection_id) references Collections(id)"
		");",
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	//----------�Q�[���쐬-------------
	err = sqlite3_exec(db,
		"CREATE TABLE Games("
		"id integer primary key,"
		"name text"
		");"
		,
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	//--------�Q�[���X�R�A�쐬------------
	err = sqlite3_exec(db,
		"CREATE TABLE GameScores("
		"id integer primary key autoincrement,"
		"user_id integer,"
		"game_id integer,"
		"score1 integer default 0,"
		"score2 integer default 0,"
		"score3 integer default 0,"
		"score4 integer default 0,"
		"play_date text,"
		"foreign key (user_id) references Users(id)"
		"foreign key (game_id) references Games(id)"
		");"
		,
		NULL, NULL, &errMsg);

	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	//----------�����f�[�^����---------

	//-----------���[�U�[�f�[�^����----------
	err = sqlite3_exec(db,
		"INSERT INTO Users VALUES(1, '', 0, 0, '');"
		"INSERT INTO Users VALUES(2, '', 0, 0, '');"
		"INSERT INTO Users VALUES(3, '', 0, 0, '');",
		NULL, NULL, &errMsg);
	if (err != SQLITE_OK) {
		sqlite3_free(errMsg);
		return false;
	}
	return true;
}
sqlite3* MySqlite3::getDB() {//�f�[�^�x�[�X�ւ̃|�C���^���Q�Ƃ���
	return db;
}