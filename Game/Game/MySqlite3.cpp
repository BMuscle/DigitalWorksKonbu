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
	//-------アイテム作成-------------
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
	//-----------ゲームデータ投入----------------------------
	insertGames();
	//-----------ガチャデータ投入----------------------------
	insertItems();//アイテムデータ投入

	return true;
}
sqlite3* MySqlite3::getDB() {//データベースへのポインタを参照する
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
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	//SQLバインド用
	CSVData csv;

	//---------------------サッカーデータ---------------------------------------
	csv.load(U"resources/gamedata/soccer.csv");
	for (int row = 0; row < csv.rows(); row++, auto_item_id++) {
		//アイテム表にアイテムを追加する
		int id = csv.get<int>(row, 0);
		std::string ENname = csv.get<String>(row, 1).toUTF8();//エンコード済みの名前 UTF-32→UTF-8で保存する
		//items表に追加
		std::string sql = "INSERT INTO Items(key, game_id, name) VALUES(?, 1, ?);";
		//ステートメント作成
		sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		//ステートハンドラ一旦初期化
		sqlite3_reset(stmt);
		//1つ目の？をidにする
		sqlite3_bind_int(stmt, 1, id);
		//2つ目の？をnameにする
		sqlite3_bind_text(stmt, 2, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);
		//SQL実行
		sqlite3_step(stmt);
		//ステートメント消去
		sqlite3_finalize(stmt);

		for (int user_id = 1; user_id <= 3; user_id++) {//３人分の初期アイテムを作成する
			//items表に追加
			std::string sql = "INSERT INTO UserItems(user_id, item_id, game_id, flag) VALUES (?, ?, 1, 0);";
			//ステートメント作成
			sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
			//ステートハンドラ一旦初期化
			sqlite3_reset(stmt);

			//1つ目の？をidにする
			sqlite3_bind_int(stmt, 1, user_id);
			//2つ目の？をitemにする
			sqlite3_bind_int(stmt, 2, auto_item_id);

			//SQL実行
			sqlite3_step(stmt);
			//ステートメント消去
			sqlite3_finalize(stmt);
		}
	}

	//---------------------靴飛ばしデータ---------------------------------------
	csv.load(U"resources/gamedata/shoekick.csv");
	for (int row = 0; row < csv.rows(); row++, auto_item_id++) {
		//アイテム表にアイテムを追加する
		int id = csv.get<int>(row, 0);
		std::string ENname = csv.get<String>(row, 1).toUTF8();//エンコード済みの名前 UTF-32→UTF-8で保存する
		//items表に追加
		std::string sql = "INSERT INTO Items(key, game_id, name) VALUES(?, 2, ?);";
		//ステートメント作成
		sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		//ステートハンドラ一旦初期化
		sqlite3_reset(stmt);
		//1つ目の？をidにする
		sqlite3_bind_int(stmt, 1, id);
		//2つ目の？をnameにする
		sqlite3_bind_text(stmt, 2, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);
		//SQL実行
		sqlite3_step(stmt);
		//ステートメント消去
		sqlite3_finalize(stmt);

		for (int user_id = 1; user_id <= 3; user_id++) {//３人分の初期アイテムを作成する
			//items表に追加
			std::string sql = "INSERT INTO UserItems(user_id, item_id, game_id, flag) VALUES(?, ?, 2, 0);";
			//ステートメント作成
			sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
			//ステートハンドラ一旦初期化
			sqlite3_reset(stmt);
			//1つ目の？をidにする
			sqlite3_bind_int(stmt, 1, user_id);
			//2つ目の？をitemにする
			sqlite3_bind_int(stmt, 2, auto_item_id);

			//SQL実行
			sqlite3_step(stmt);
			//ステートメント消去
			sqlite3_finalize(stmt);
		}
	}


	//---------------------ドッジボールデータ---------------------------------------
	csv.load(U"resources/gamedata/dodge.csv");
	for (int row = 0; row < csv.rows(); row++, auto_item_id++) {
		//アイテム表にアイテムを追加する
		int id = csv.get<int>(row, 0);
		std::string ENname = csv.get<String>(row, 1).toUTF8();//エンコード済みの名前 UTF-32→UTF-8で保存する
		//items表に追加
		std::string sql = "INSERT INTO Items(key, game_id, name) VALUES(?, 3, ?);";
		//ステートメント作成
		sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
		//ステートハンドラ一旦初期化
		sqlite3_reset(stmt);
		//1つ目の？をidにする
		sqlite3_bind_int(stmt, 1, id);
		//2つ目の？をnameにする
		sqlite3_bind_text(stmt, 2, ENname.c_str(), (int)ENname.size(), SQLITE_TRANSIENT);
		//SQL実行
		sqlite3_step(stmt);
		//ステートメント消去
		sqlite3_finalize(stmt);

		for (int user_id = 1; user_id <= 3; user_id++) {//３人分の初期アイテムを作成する
			//items表に追加
			std::string sql = "INSERT INTO UserItems(user_id, item_id, game_id, flag) VALUES(?, ?, 3, 0);";
			//ステートメント作成
			sqlite3_prepare_v2(MySqlite3::getDB(), sql.c_str(), (int)sql.size(), &stmt, &pzTest);
			//ステートハンドラ一旦初期化
			sqlite3_reset(stmt);
			//1つ目の？をidにする
			sqlite3_bind_int(stmt, 1, user_id);
			//2つ目の？をitemにする
			sqlite3_bind_int(stmt, 2, auto_item_id);

			//SQL実行
			sqlite3_step(stmt);
			//ステートメント消去
			sqlite3_finalize(stmt);
		}
	}
	
}