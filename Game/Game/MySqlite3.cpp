#include "MySqlite3.h"

sqlite3* MySqlite3::db;

/* SQL実行
//-------------------------
err = sqlite3_exec(db,
	,
	NULL, NULL, &errMsg);

if (err != SQLITE_OK) {
	sqlite3_free(errMsg);
	return false;
}
*/
bool MySqlite3::initialize() {	//初期化 DBの初期化を行う
	int err = sqlite3_open("savedata.db", &db);
	if (err != SQLITE_OK) {
		//エラー処理
		return false;//DBのオープン失敗
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
	//-------ユーザー作成---------
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
	//-------アイテム作成-------------
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
	//--------コレクション作成----------
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
	//-------ユーザーアイテム作成------
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
	//----------ユーザーコレクション作成---------
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
	//----------ゲーム作成-------------
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
	//--------ゲームスコア作成------------
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
	//----------初期データ投入---------

	//-----------ユーザーデータ投入----------
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
sqlite3* MySqlite3::getDB() {//データベースへのポインタを参照する
	return db;
}