#include "User.h"

int User::user_id;
String User::user_name;

void User::initialize() {	//初期化

}
void User::finalize() {		//終了化

}

bool User::saveDataAccess(int id) {
	user_id = id;
}

bool User::createSaveData(int id, String name) {//ユーザーデータ作成
	sqlite3_stmt* stmt = NULL;//ステートメントハンドル
	const char* pzTest;
	//----------ユーザーデータ更新-----------
	//SQLバインド用
	std::string sql = "UPDATE Users SET name = ?, play_start_date = date('now')"
		"WHERE id = ?;";

	//ステートメント作成
	sqlite3_prepare_v2(MySqlite3::getDB(),sql.c_str(), sql.size(), &stmt, &pzTest);
	//ステートハンドラ一旦初期化
	sqlite3_reset(stmt);
	//バインド
	sqlite3_bind_text(stmt, 1, name.narrow().c_str(), name.size(), SQLITE_TRANSIENT);//1つ目の？をnameにする
	sqlite3_bind_int(stmt, 2, id);//2つ目の？をidにする
	sqlite3_step(stmt);//SQL実行
	sqlite3_finalize(stmt);//ステートメント消去

	//ここでユーザーデータを取得させる
	saveDataAccess(id);
	return true;
}

