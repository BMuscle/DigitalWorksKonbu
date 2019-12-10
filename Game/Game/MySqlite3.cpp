#include "MySqlite3.h"

sqlite3* MySqlite3::db;


bool MySqlite3::initialize() {	//初期化 DBの初期化を行う
	int err = sqlite3_open("savedata.db", &db);
	if (err != SQLITE_OK) {
		//エラー処理
		return false;//DBのオープン失敗
	}
	return true;//DBのオープン成功
}
bool MySqlite3::finalize() {		//終了化
	int err = sqlite3_close(db);
	if (err != SQLITE_OK) {
		//エラー処理
		return false;	//DBのクローズ失敗
	}
	return true;//DBのクローズ成功
}
bool MySqlite3::DBCREATE() {		//基本使用しない　データベースの初期設定を行う。 DBファイル消してから実行
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
const sqlite3* MySqlite3::getDB() {//データベースへのポインタを参照する
	return db;
}