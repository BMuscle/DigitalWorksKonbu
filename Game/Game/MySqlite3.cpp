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
	//-------�A�C�e���쐬-------------
	err = sqlite3_exec(db,
		"CREATE TABLE Items("
		"id integer primary key autoincrement,"
		"key integer,"
		"game_id integer,"
		"name text,"
		"foreign key (game_id) references Games(id)"
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
		"game_id integer,"
		"flag default 0 check(flag < 2 and flag > -1),"
		"foreign key (user_id) references Users(id),"
		"foreign key (item_id) references Items(id),"
		"foreign key (game_id) references Games(id)"
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
	//-----------�Q�[���f�[�^����----------------------------
	insertGames();
	//-----------�K�`���f�[�^����----------------------------
	insertItems();//�A�C�e���f�[�^����

	return true;
}
sqlite3* MySqlite3::getDB() {//�f�[�^�x�[�X�ւ̃|�C���^���Q�Ƃ���
	return db;
}

void MySqlite3::insertGames() {
	char* errMsg = NULL;
	int err = 0;

	err = sqlite3_exec(db,
		"INSERT INTO Games VALUES(1, 'soccer');"
		"INSERT INTO Games VALUES(2, 'shoekick');"
		"INSERT INTO Games VALUES(3, 'dodge');",
		NULL, NULL, &errMsg);
}

void MySqlite3::insertItems() {
	int auto_item_id = 1;
	sqlite3_stmt* stmt = NULL;//�X�e�[�g�����g�n���h��
	const char* pzTest;
	//SQL�o�C���h�p
	CSVData csv;

	//---------------------�T�b�J�[�f�[�^---------------------------------------
	csv.load(U"resources/gamedata/soccer.csv");
	for (int row = 0; row < csv.rows(); row++, auto_item_id++) {
		//�A�C�e���\�ɃA�C�e����ǉ�����
		int id = csv.get<int>(row, 0);
		std::string ENname = csv.get<String>(row, 1).toUTF8();//�G���R�[�h�ς݂̖��O UTF-32��UTF-8�ŕۑ�����
		//items�\�ɒǉ�
		std::string sql = "INSERT INTO Items(key, game_id, name) VALUES(?, 1, ?);";
		//�X�e�[�g�����g�쐬
		sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		//�X�e�[�g�n���h����U������
		sqlite3_reset(stmt);
		//1�ڂ́H��id�ɂ���
		sqlite3_bind_int(stmt, 1, id);
		//2�ڂ́H��name�ɂ���
		sqlite3_bind_text(stmt, 2, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);
		//SQL���s
		sqlite3_step(stmt);
		//�X�e�[�g�����g����
		sqlite3_finalize(stmt);

		for (int user_id = 1; user_id <= 3; user_id++) {//�R�l���̏����A�C�e�����쐬����
			//items�\�ɒǉ�
			std::string sql = "INSERT INTO UserItems(user_id, item_id, game_id, flag) VALUES (?, ?, 1, 0);";
			//�X�e�[�g�����g�쐬
			sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
			//�X�e�[�g�n���h����U������
			sqlite3_reset(stmt);

			//1�ڂ́H��id�ɂ���
			sqlite3_bind_int(stmt, 1, user_id);
			//2�ڂ́H��item�ɂ���
			sqlite3_bind_int(stmt, 2, auto_item_id);

			//SQL���s
			sqlite3_step(stmt);
			//�X�e�[�g�����g����
			sqlite3_finalize(stmt);
		}
	}

	//---------------------�C��΂��f�[�^---------------------------------------
	csv.load(U"resources/gamedata/shoekick.csv");
	for (int row = 0; row < csv.rows(); row++, auto_item_id++) {
		//�A�C�e���\�ɃA�C�e����ǉ�����
		int id = csv.get<int>(row, 0);
		std::string ENname = csv.get<String>(row, 1).toUTF8();//�G���R�[�h�ς݂̖��O UTF-32��UTF-8�ŕۑ�����
		//items�\�ɒǉ�
		std::string sql = "INSERT INTO Items(key, game_id, name) VALUES(?, 2, ?);";
		//�X�e�[�g�����g�쐬
		sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		//�X�e�[�g�n���h����U������
		sqlite3_reset(stmt);
		//1�ڂ́H��id�ɂ���
		sqlite3_bind_int(stmt, 1, id);
		//2�ڂ́H��name�ɂ���
		sqlite3_bind_text(stmt, 2, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);
		//SQL���s
		sqlite3_step(stmt);
		//�X�e�[�g�����g����
		sqlite3_finalize(stmt);

		for (int user_id = 1; user_id <= 3; user_id++) {//�R�l���̏����A�C�e�����쐬����
			//items�\�ɒǉ�
			std::string sql = "INSERT INTO UserItems(user_id, item_id, game_id, flag) VALUES(?, ?, 2, 0);";
			//�X�e�[�g�����g�쐬
			sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
			//�X�e�[�g�n���h����U������
			sqlite3_reset(stmt);
			//1�ڂ́H��id�ɂ���
			sqlite3_bind_int(stmt, 1, user_id);
			//2�ڂ́H��item�ɂ���
			sqlite3_bind_int(stmt, 2, auto_item_id);

			//SQL���s
			sqlite3_step(stmt);
			//�X�e�[�g�����g����
			sqlite3_finalize(stmt);
		}
	}


	//---------------------�h�b�W�{�[���f�[�^---------------------------------------
	csv.load(U"resources/gamedata/dodge.csv");
	for (int row = 0; row < csv.rows(); row++, auto_item_id++) {
		//�A�C�e���\�ɃA�C�e����ǉ�����
		int id = csv.get<int>(row, 0);
		std::string ENname = csv.get<String>(row, 1).toUTF8();//�G���R�[�h�ς݂̖��O UTF-32��UTF-8�ŕۑ�����
		//items�\�ɒǉ�
		std::string sql = "INSERT INTO Items(key, game_id, name) VALUES(?, 3, ?);";
		//�X�e�[�g�����g�쐬
		sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		//�X�e�[�g�n���h����U������
		sqlite3_reset(stmt);
		//1�ڂ́H��id�ɂ���
		sqlite3_bind_int(stmt, 1, id);
		//2�ڂ́H��name�ɂ���
		sqlite3_bind_text(stmt, 2, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);
		//SQL���s
		sqlite3_step(stmt);
		//�X�e�[�g�����g����
		sqlite3_finalize(stmt);

		for (int user_id = 1; user_id <= 3; user_id++) {//�R�l���̏����A�C�e�����쐬����
			//items�\�ɒǉ�
			std::string sql = "INSERT INTO UserItems(user_id, item_id, game_id, flag) VALUES(?, ?, 3, 0);";
			//�X�e�[�g�����g�쐬
			sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
			//�X�e�[�g�n���h����U������
			sqlite3_reset(stmt);
			//1�ڂ́H��id�ɂ���
			sqlite3_bind_int(stmt, 1, user_id);
			//2�ڂ́H��item�ɂ���
			sqlite3_bind_int(stmt, 2, auto_item_id);

			//SQL���s
			sqlite3_step(stmt);
			//�X�e�[�g�����g����
			sqlite3_finalize(stmt);
		}
	}
	
}